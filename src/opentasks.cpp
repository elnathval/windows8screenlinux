#include "engine/rendering.h"
#include <iostream>
#include <unistd.h>

bool openingTask = false;

void Update() {
    if(!IsWindowFocused()) openingTask = true;

    for (Tile* tileptr : mainPanel.tiles) {
        if (tileptr->isLeftClicked()) {

            if (tileptr->command == "desktop") {
                openingTask = true;
                
            } else {
                if(fork() == 0) {
                    system(tileptr->command.c_str());
                }
                openingTask = true;
            }
        }
        
    }
}
