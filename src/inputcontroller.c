#include "raylib.h"
#include "tilerenderer.h"

struct Tile clickedTile = {0, 0, 0, 0, {0}, "", ""};


void FrameEvent(){
    clickedTile = (struct Tile){0, 0, 0, 0, {0}, "", ""};
    if(IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
        int mouseX = GetMouseX();
        int mouseY = GetMouseY();
        struct Tile *programTiles = tiles;
        for (int i = 0; i < 2; i++) {
            if (mouseX >= programTiles[i].x && mouseX <= programTiles[i].x + programTiles[i].width &&
                mouseY >= programTiles[i].y && mouseY <= programTiles[i].y + programTiles[i].height) {
                clickedTile = programTiles[i];
                break;
            }
        }
    }

    int mouseX = GetMouseX();
    int mouseY = GetMouseY();
    struct Tile *programTiles = tiles;
    for (int i = 0; i < 2; i++) {
        if (mouseX >= programTiles[i].x && mouseX <= programTiles[i].x + programTiles[i].width &&
            mouseY >= programTiles[i].y && mouseY <= programTiles[i].y + programTiles[i].height) {
            clickedTile = programTiles[i];
            break;
        }
    }
}
