#include "engine/rendering.h"
#include <iostream>

void Update() {
    for (Tile* tileptr : mainPanel.tiles) {
        if (tileptr->isLeftClicked()) {
            // For now, just change the color of the tile when it's clicked
            tileptr->changeColor((Color){ 255, 0, 0, 255 });
        }
        else {
            // Change it back to its original color when it's not clicked
            tileptr->changeColor((Color){ 0, 120, 215, 255 });
        }
    }
}
