#include "raylib.h"
#include "resource_dir.h"
#include <stdio.h>
#include "graphic-objects.h"


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

float horizontalMargin, verticalMargin;

int changeBackgroundColor(Color newColor)
{
    defaultBackgroundColor = newColor;
    return 0;
}

Font SegoeUI;

Panel mainPanel;

void Render()
{
    
    // Setup the back buffer for drawing (clear cºolor and depth buffers)
	ClearBackground(defaultBackgroundColor);
	// draw some text using the default font
	DrawTextEx(SegoeUI,"Start", (Vector2){ horizontalMargin, 60 }, 90, 2, WHITE);

    DrawRectangle(horizontalMargin, GetScreenHeight() - 100, 50, 50, WHITE); 

    mainPanel.Draw();

}

void LoadResources()
{
    SegoeUI = LoadFontEx("SegoeUIVF.ttf", 90, NULL, 0);

    // Load the font we want to use for drawing text
    horizontalMargin = GetScreenWidth() * 0.1;
    verticalMargin = GetScreenHeight() * 0.2;
    tileSize = GetScreenHeight() * 0.7 / 4;
    tileMargin = 5;

    mainPanel = Panel(horizontalMargin, verticalMargin, GetScreenWidth() - 2 * horizontalMargin, GetScreenHeight() - 2 * verticalMargin);
    Tile desktop = Tile(0, 0, 2, 1, (Color){ 0, 120, 215, 255 }, "Desktop", "");
    Tile mail = Tile(0, 1, 1, 1, (Color){ 0, 120, 215, 255 }, "Mail", "");
    mainPanel.add(desktop);
    mainPanel.add(mail);

    mainPanel.font = SegoeUI;
}


void UnloadResources()
{
    UnloadFont(SegoeUI);
}
