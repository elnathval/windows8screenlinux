#include <fstream>
#include "rendering.h"
#include <iostream>
#include <stdlib.h>
#include <thread>
#include <vector>

std::map<std::string, std::string> appNames;

void DefaultTileConfig() {
    Tile *mail = new Tile(0, 0, 4, 2, (Color){ 0, 120, 215, 255 }, "Mail", "xdg-open mailto:");
    Tile *desktop = new Tile(4, 0, 4, 2, (Color){ 0, 120, 215, 255 }, "Desktop", "desktop");
    Tile *calendar = new Tile(0, 2, 4, 2, (Color){ 138, 57, 191, 255 }, "Calendar", "xdg-open webcal:");
    Tile *explorer = new Tile(4, 2, 2, 2, (Color){ 57, 191, 153, 255 }, "Files", "xdg-open ~");
    Tile *finances = new Tile(0, 4, 4, 2, (Color){ 30, 117, 38, 255 }, "Finance", "xdg-open https://www.google.com/finance/");
    Tile *browser = new Tile(4, 4, 2, 2, (Color){ 47, 121, 181, 255 }, "Browser", "xdg-open https://www.google.com/");
    mainPanel->add(desktop);
    mainPanel->add(mail);
    mainPanel->add(calendar);
    mainPanel->add(explorer);
    mainPanel->add(finances);
    mainPanel->add(browser);

    char configDir[256];
    snprintf(configDir, sizeof(configDir), "%s/.config/windows8screenlinux", getenv("HOME"));
    system((std::string("mkdir -p ") + configDir).c_str());

    std::ofstream tile_config;
    tile_config.open(configDir + std::string("/tiles.bin"), std::ios::out|std::ios::binary);
    
    if (!tile_config.is_open())
    {
        std::cout<<configDir<<std::endl;
    }
    
    for (Tile* tileptr : mainPanel->tiles) {
        tile_config.write((char*)&tileptr->gridX, sizeof(int));
        tile_config.write((char*)&tileptr->gridY, sizeof(int));
        tile_config.write((char*)&tileptr->width, sizeof(int));
        tile_config.write((char*)&tileptr->height, sizeof(int));
        tile_config.write((char*)&tileptr->backgroundColor.r, sizeof(unsigned char));
        tile_config.write((char*)&tileptr->backgroundColor.g, sizeof(unsigned char));
        tile_config.write((char*)&tileptr->backgroundColor.b, sizeof(unsigned char));
        tile_config.write((char*)&tileptr->backgroundColor.a, sizeof(unsigned char));
        size_t labelSize = tileptr->label.size();
        size_t commandSize = tileptr->command.size();
        tile_config.write((char*)&labelSize, sizeof(size_t));
        tile_config.write(tileptr->label.c_str(), labelSize);
        tile_config.write((char*)&commandSize, sizeof(size_t));
        tile_config.write(tileptr->command.c_str(), commandSize);
    }
    tile_config.close();
}

void LoadTiles(){
    char configDir[256];
    snprintf(configDir, sizeof(configDir), "%s/.config/windows8screenlinux", getenv("HOME"));
    system((std::string("mkdir -p ") + configDir).c_str());

    std::ifstream tile_config(configDir + std::string("/tiles.bin"), std::ios::in|std::ios::binary);
    if (!tile_config.is_open()) {
        std::cout<<"No tile configuration found, loading default configuration."<<std::endl;
        DefaultTileConfig();
        return;
    }
    char line[256];
    while (tile_config.read(line, sizeof(int) * 4 + sizeof(unsigned char) * 4)) {
        int gridX = *(int*)(line);
        int gridY = *(int*)(line + sizeof(int));
        int width = *(int*)(line + 2 * sizeof(int));
        int height = *(int*)(line + 3 * sizeof(int));
        unsigned char r = *(unsigned char*)(line + 4 * sizeof(int));
        unsigned char g = *(unsigned char*)(line + 4 * sizeof(int) + sizeof(unsigned char));
        unsigned char b = *(unsigned char*)(line + 4 * sizeof(int) + 2 * sizeof(unsigned char));
        unsigned char a = *(unsigned char*)(line + 4 * sizeof(int) + 3 * sizeof(unsigned char));
        size_t labelSize;
        tile_config.read((char*)&labelSize, sizeof(size_t));
        char* labelBuffer = new char[labelSize + 1];
        tile_config.read(labelBuffer, labelSize);
        labelBuffer[labelSize] = '\0';
        std::string label(labelBuffer);
        delete[] labelBuffer;
        size_t commandSize;
        tile_config.read((char*)&commandSize, sizeof(size_t));
        char* commandBuffer = new char[commandSize + 1];
        tile_config.read(commandBuffer, commandSize);
        commandBuffer[commandSize] = '\0';
        std::string command(commandBuffer);
        delete[] commandBuffer;

        Tile* tileptr = new Tile(gridX, gridY, width, height, (Color){ r, g, b, a }, label, command);
        mainPanel->add(tileptr);
    }

    tile_config.close();

}

void ParseApplicationFile(std::string filePath) {
    std::ifstream appFile(filePath);
    if (!appFile.is_open()) {
        std::cout<<"Failed to open application file: "<<filePath<<std::endl;
        return;
    }
    std::string line;
    std::string name;
    std::string exec;
    std::string icon;
    bool noDisplay = false;
    std::getline(appFile,line);
    if(line != "[Desktop Entry]"){
        std::cout<<"Not an entry"<<std::endl;
        return;
    }
    while (std::getline(appFile, line)) {
        if (line.rfind("Name=", 0) == 0) {
            name = line.substr(5);
        } else if (line.rfind("Exec=", 0) == 0) {
            exec = line.substr(5);
        } else if (line.rfind("Icon=", 0) == 0) {
            icon = line.substr(5);
        } else if (line.rfind("NoDisplay") == 0) {
            noDisplay = (line.substr(10) == "true");
        } else if(line == "") break;
    }
    appFile.close();
    if (name.empty() || exec.empty() || noDisplay) {
        std::cout<<"Invalid application file: "<<filePath<<std::endl;
        return;
    }
    for (const std::string code : {"%f","%F","%u","%U","%i","%c","%k","%%"}) {
        size_t pos;
        while ((pos = exec.find(code)) != std::string::npos)
            exec.erase(pos, code.size());
    }

    while (exec.find("  ") != std::string::npos) exec.replace(exec.find("  "), 2, " ");

    std::cout<<"Parsed application: "<<name<<" with command: "<<exec<<" and icon: "<<icon<<std::endl;
    int order = appNames.size();
    appNames[name] = exec;

    
    
    //ListItem* appListItem =new ListItem(name, {0}, exec, 4, 2, 0, order);
    //appsPanel->add(appListItem);
}

void PushItems(){
    int order = 0;
    for(auto i = appNames.begin(); i != appNames.end(); i++){
        //Texture sigma = LoadTexture("mail.png");
        ListItem* appListItem =new ListItem(i->first, {0}, i->second, 4, 1, 4* (order / 10), order % 10);
        appsPanel->add(appListItem);
        order++;
    }
    
}

void GetApplications() {
    
    FilePathList rootApplications = LoadDirectoryFiles("/usr/share/applications");
    FilePathList userApplications = LoadDirectoryFiles((std::string(getenv("HOME")) + "/.local/share/applications").c_str());
    FilePathList snapApplications = LoadDirectoryFiles("/var/lib/snapd/desktop/applications");
    FilePathList allApplications;
    for (unsigned int i = 0; i < rootApplications.count; i++) {
        ParseApplicationFile(rootApplications.paths[i]);
    }
    for (unsigned int i = 0; i < userApplications.count; i++) {
        ParseApplicationFile(userApplications.paths[i]);
    }
    for (unsigned int i = 0; i < snapApplications.count; i++) {
        ParseApplicationFile(snapApplications.paths[i]);
    }


    PushItems();
    
}


