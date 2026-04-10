#include "raylib.h"
#include "resource_dir.h"
#include "tilerenderer.h"
#include <stdio.h>
#include "inputcontroller.h"

Color windowsPurple = (Color){ 24, 0, 83, 255 };

Color defaultBackgroundColor = (Color){ 24, 0, 83, 0 };

struct ProgramRectangle {
    int x;
    int y;
    int width;
    int height;
    Color backgroundColor;
    char *label;
    char *command;
};

int horizontalMargin, verticalMargin, tileSize, tileMargin;

int changeBackgroundColor(Color newColor)
{
    defaultBackgroundColor = newColor;
    return 0;
}

Font SegoeUI;

void Render()
{
    
    // Setup the back buffer for drawing (clear cºolor and depth buffers)
	ClearBackground(defaultBackgroundColor);
	// draw some text using the default font
	DrawTextEx(SegoeUI,"Start", (Vector2){ horizontalMargin, 60 }, 90, 2, WHITE);

    DrawRectangle(horizontalMargin, GetScreenHeight() - 100, 50, 50, WHITE);


    GetTiles();    
    struct Tile *programTiles = tiles;
    struct Tile clicked = clickedTile;
    
    if (programTiles == NULL) {
        return;
    }
    for (int i = 0; i < 2; i++) {
        if (clicked.x == programTiles[i].x && clicked.y == programTiles[i].y) {
            DrawRectangle(programTiles[i].x, programTiles[i].y, programTiles[i].width, programTiles[i].height, RED);
        } else {
            DrawRectangle(programTiles[i].x, programTiles[i].y, programTiles[i].width, programTiles[i].height, programTiles[i].backgroundColor);
        }
        DrawRectangle(programTiles[i].x, programTiles[i].y, programTiles[i].width, programTiles[i].height, programTiles[i].backgroundColor);
    }

}

void LoadResources()
{
    // Load the font we want to use for drawing text
    SegoeUI = LoadFontEx("SegoeUIVF.ttf", 90, NULL, 0);
    horizontalMargin = GetScreenWidth() * 0.1;
    verticalMargin = GetScreenHeight() * 0.2;
    tileSize = GetScreenHeight() * 0.7 / 4;
    tileMargin = 5;
}


void UnloadResources()
{
    
    UnloadFont(SegoeUI);
}
