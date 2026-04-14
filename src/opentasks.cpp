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
            if(usercontroptr->name == "Down"){
                //openingTask = true;
            } else if (usercontroptr->name == "Shutdown"){
                
                delete shutdownPanel;


                (shutdownMenu) ? shutdownMenu = false : shutdownMenu = true;

                if(shutdownMenu){
                    shutdownPanel = new Panel(GetScreenWidth()-300, 150);
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
                //system("systemctl poweroff");
            } else if (usercontroptr->name == "Search"){
                //system("xdg-open https://www.google.com/");
            }
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
}
