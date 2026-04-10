#include "raylib.h"
#include "resource_dir.h"
#include <stdio.h>
#include "graphic-objects.h"


Color windowsPurple = (Color){ 24, 0, 83, 255 };

Color defaultBackgroundColor = (Color){ 24, 0, 83, 0 };


float horizontalMargin, verticalMargin;

int changeBackgroundColor(Color newColor)
{
    defaultBackgroundColor = newColor;
    return 0;
}

Font SegoeUI;

Panel mainPanel;

void InitialAnimation(){
    for(float i = 1; i > 0; i -= 0.15f){
        BeginDrawing();
        SetWindowOpacity(1-i);
        ClearBackground(defaultBackgroundColor);
        EndDrawing();
    }
    SetWindowOpacity(1);
    for(float i = 0; i < 1; i += 0.15f){
        Color loadingWhite = (Color){ 255, 255, 255, 255.0f * i};
        BeginDrawing();
        ClearBackground(defaultBackgroundColor);
        DrawTextEx(SegoeUI,"Start", (Vector2){ horizontalMargin, 60 }, 90, 2, loadingWhite);
        EndDrawing();
    }

    for(float i = 0.5; i > 0; i -= 0.15f * (i + 0.015f)){
        Color loadingWhite = (Color){ 255, 255, 255, 255.0f * (1 - 2*i)};
        BeginDrawing();
        ClearBackground(defaultBackgroundColor);
        DrawTextEx(SegoeUI,"Start", (Vector2){ horizontalMargin, 60 }, 90, 2, WHITE);
        mainPanel.Draw(i);
        DrawRectangle(horizontalMargin, GetScreenHeight() - 100, 50, 50, loadingWhite); 
        EndDrawing();
    }
}

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
    Tile *desktop = new Tile(0, 0, 2, 1, (Color){ 0, 120, 215, 255 }, "Desktop", "desktop");
    Tile *mail = new Tile(0, 1, 1, 1, (Color){ 0, 120, 215, 255 }, "Mail", "thunderbird");
    mainPanel.add(desktop);
    mainPanel.add(mail);

    mainPanel.font = SegoeUI;
}


void UnloadResources()
{
    UnloadFont(SegoeUI);
    for (Tile* tileptr : mainPanel.tiles) {
        delete tileptr;
    }
}

void FinalAnimation(){
    for(float i = 1; i > 0; i -= 0.20f){
		BeginDrawing();
        ClearBackground(defaultBackgroundColor);
		SetWindowOpacity(i);
		EndDrawing();
	}
}