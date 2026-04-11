#include <fstream>
#include "rendering.h"
#include <iostream>
#include <stdlib.h>



void DefaultTileConfig() {
    Tile *mail = new Tile(0, 0, 2, 1, (Color){ 0, 120, 215, 255 }, "Mail", "xdg-open mailto:");
    Tile *desktop = new Tile(2, 0, 2, 1, (Color){ 0, 120, 215, 255 }, "Desktop", "desktop");
    Tile *calendar = new Tile(0, 1, 2, 1, (Color){ 138, 57, 191, 255 }, "Calendar", "xdg-open webcal:");
    Tile *explorer = new Tile(2, 1, 1, 1, (Color){ 57, 191, 153, 255 }, "Files", "xdg-open ~");
    Tile *finances = new Tile(0, 2, 2, 1, (Color){ 30, 117, 38, 255 }, "Finances", "xdg-open https://www.google.com/finance/");
    Tile *browser = new Tile(2, 2, 1, 1, (Color){ 47, 121, 181, 255 }, "Browser", "xdg-open https://www.google.com/");
    mainPanel.add(desktop);
    mainPanel.add(mail);
    mainPanel.add(calendar);
    mainPanel.add(explorer);
    mainPanel.add(finances);
    mainPanel.add(browser);

    char configDir[256];
    snprintf(configDir, sizeof(configDir), "%s/.config/windows8screenlinux", getenv("HOME"));
    system((std::string("mkdir -p ") + configDir).c_str());

    std::ofstream tile_config;
    tile_config.open(configDir + std::string("/tiles.bin"), std::ios::out|std::ios::binary);
    
    if (!tile_config.is_open())
    {
        std::cout<<configDir<<std::endl;
    }
    
    for (Tile* tileptr : mainPanel.tiles) {
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
        mainPanel.add(tileptr);
    }

    tile_config.close();

}

