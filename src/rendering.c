#include "raylib.h"
#include "resource_dir.h"
#include "tilerenderer.h"
#include <stdio.h>

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


int changeBackgroundColor(Color newColor)
{
    defaultBackgroundColor = newColor;
    return 0;
}

void Render()
{
    int horizontalMargin = GetScreenWidth() * 0.1;
    // Setup the back buffer for drawing (clear cºolor and depth buffers)
	ClearBackground(defaultBackgroundColor);
	// draw some text using the default font
	DrawText("Start", horizontalMargin,60,90,WHITE);

    DrawRectangle(horizontalMargin, GetScreenHeight() - 100, 50, 50, WHITE);


    GetTiles();    
    struct Tile *programTiles = tiles;
    
    if (programTiles == NULL) {
        printf("Error al obtener los tiles");
        return;
    }
    for (int i = 0; i < 2; i++) {
        printf("Cargando tiles");
        DrawRectangle(programTiles[i].x, programTiles[i].y, programTiles[i].width, programTiles[i].height, programTiles[i].backgroundColor);
    }

}

