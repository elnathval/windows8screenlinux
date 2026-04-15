#include "engine/rendering.h"
#include <iostream>
#include <unistd.h>
#include <csignal>

bool openingTask = false;

bool shutdownMenu = false;

Panel* shutdownPanel = new Panel(0,0);
ListItem* shutdownOption;
ListItem* restartOption;

void killSignal(int){
    openingTask = true;
}
 
bool showStartScreen = true;
bool buttonsEnabled = true;
float offset = 1;
float lastScrollValue = 0;

void Update() {
    signal(SIGUSR1, killSignal);

    if(!IsWindowFocused()) openingTask = true;

    for (Tile* tileptr : mainPanel->tiles) {
        if (tileptr->isLeftClicked()) {
            //Default settings
            if (tileptr->command == "desktop") {
                openingTask = true;
                
            }
            else {
                if(fork() == 0) {
                    system(tileptr->command.c_str());
                }
                openingTask = true;
            }
        }
        
    }

    for(UserControl* usercontroptr : mainPage.userControls){
        if(usercontroptr->isMouseOver()){
            usercontroptr->backgroundColor = (Color){ 255, 255, 255, 50 };
        } else {
            usercontroptr->backgroundColor = (Color){ 0, 0, 0, 0 };
        }
        
        if(usercontroptr->clicked()){
            if(usercontroptr->name == "Down" && showStartScreen){
                offset = 0;
                showStartScreen = false;
                buttonsEnabled = false;
            } else if (usercontroptr->name == "Shutdown"){
                
                delete shutdownPanel;


                (shutdownMenu) ? shutdownMenu = false : shutdownMenu = true;

                if(shutdownMenu){
                    shutdownPanel = new Panel(GetScreenWidth()-315, 150);
                    shutdownPanel->opacity = 0;
                    shutdownPanel->font = SegoeUI;
                    shutdownOption = new ListItem("Shutdown", {0}, "systemctl poweroff", 2, 1, 0, 0);
                    restartOption = new ListItem("Restart", {0}, "systemctl reboot", 2, 1, 0, 1);
                    shutdownOption->backgroundColor = (Color){ 255, 255, 255, 255 };
                    restartOption->backgroundColor = (Color){ 255, 255, 255, 255 };
                    shutdownOption->textColor = BLACK;
                    restartOption->textColor = BLACK;
                    shutdownPanel->add(shutdownOption);
                    shutdownPanel->add(restartOption);
                    mainPage.panels.push_back(shutdownPanel);
                } else {
                    usercontroptr->backgroundColor = (Color){ 0, 0, 0, 0 };
                    mainPage.panels.pop_back();
                    shutdownPanel = new Panel(0,0);
                }
            } else if (usercontroptr->name == "Search"){
                //system("xdg-open https://www.google.com/");
            }
        }
    }

    for(UserControl* usercontroptr : appsPage.userControls){
        if(usercontroptr->isMouseOver()){
            usercontroptr->backgroundColor = (Color){ 255, 255, 255, 50 };
        } else {
            usercontroptr->backgroundColor = (Color){ 0, 0, 0, 0 };
        }
        
        if(usercontroptr->name == "Up" && !showStartScreen && usercontroptr->clicked() ==  true){
            offset = 0;
            showStartScreen = true;
            buttonsEnabled = false;
        }
    }

    if(showStartScreen){
        if(offset * offset < 0.95f){
            offset += 0.04f;
            appsPage.Move(appsPage.x, GetScreenHeight()*offset*offset);
            mainPage.Move(mainPage.x, GetScreenHeight()*offset*offset - GetScreenHeight());
        } else {
            appsPage.Move(appsPage.x,GetScreenHeight());
            mainPage.Move(mainPage.x,0);
            buttonsEnabled = true;
        }
            
        
    } else {
        if(offset * offset < 0.95f){
            offset += 0.04f;
            mainPage.Move(mainPage.x, -GetScreenHeight()*(offset*offset));
            appsPage.Move(appsPage.x, GetScreenHeight() - GetScreenHeight()*offset*offset);
        } else {
            mainPage.Move(mainPage.x,-GetScreenHeight());
            appsPage.Move(appsPage.x,0);
            buttonsEnabled = true;
        }
        
        
        
    }

    if(shutdownMenu){
        if (shutdownPanel->opacity < 1){
            shutdownPanel->opacity += 0.10f;
        }  else {
            shutdownPanel->opacity = 1;
        }
    }

    for (ListItem* listitemptr : shutdownPanel->listItems){
        if(listitemptr->clicked()){
            system(listitemptr->command.c_str());
        }

        if(listitemptr->isMouseOver()){
            listitemptr->backgroundColor = LIGHTGRAY;
        } else {
            listitemptr->backgroundColor = WHITE;
        }
    }

    for (ListItem* listitemptr : appsPanel->listItems){
        if(listitemptr->clicked()){
            if(fork() == 0) {
                    system(listitemptr->command.c_str());
                }
                openingTask = true;
        }

        if(listitemptr->isMouseOver()){
            listitemptr->backgroundColor = (Color){255,255,255,50};
        } else {
            listitemptr->backgroundColor = (Color){0,0,0,0};
        }
    }
    
}
