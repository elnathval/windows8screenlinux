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

Panel* mainPanel;
Label* startLabel;
UserControl* downButton;

Page mainPage("Start", 0, 0);

void InitialAnimation(){
    for(float i = 1; i > 0; i -= 0.15f){
        BeginDrawing();
        SetWindowOpacity(1-i);
        ClearBackground(defaultBackgroundColor);
        EndDrawing();
    }
    
    SetWindowOpacity(1);
    mainPanel->opacity = 0.0f;
    downButton->opacity = 0.0f;

    for(float i = 0; i < 1; i += 0.15f){
        Color loadingWhite = (Color){ 255, 255, 255, 255.0f * i};
        BeginDrawing();
        ClearBackground(defaultBackgroundColor);
        

        startLabel->opacity = i;
        mainPage.Draw();

        EndDrawing();
    }

    startLabel->opacity = 1.0f;

    for(float i = 0.5; i > 0; i -= 0.15f * (i + 0.015f)){
        Color loadingWhite = (Color){ 255, 255, 255, 255.0f * (1 - 2*i)};
        BeginDrawing();
        ClearBackground(defaultBackgroundColor);

        float panelOffsetX = horizontalMargin + tileSize * 2 * i;
        float panelOffsetY = verticalMargin + tileSize * i;
        mainPanel->Move(panelOffsetX, panelOffsetY);
        mainPanel->opacity = 1 - 2*i;
        mainPage.Draw();

        downButton->opacity = 1 - 2*i;
 
        EndDrawing();
    }

    mainPanel->opacity = 1.0f;
}

void Render()
{
    
    // Setup the back buffer for drawing (clear cºolor and depth buffers)
	ClearBackground(defaultBackgroundColor);
	// draw some text using the default font

    mainPage.Draw();

}

void LoadResources()
{
    SegoeUI = LoadFontEx("SegoeUIVF.ttf", 90, NULL, 0);

    Texture mail = LoadTexture("mail.png");
    Texture calendar = LoadTexture("calendar.png");
    Texture finance = LoadTexture("finance.png");
    Texture browser = LoadTexture("ie.png");
    Texture explorer = LoadTexture("explorer.png");

    textureMap["Mail"] = mail;
    textureMap["Calendar"] = calendar;
    textureMap["Finance"] = finance;
    textureMap["Browser"] = browser;
    textureMap["Files"] = explorer;


    horizontalMargin = GetScreenWidth() * 0.1;
    verticalMargin = GetScreenHeight() * 0.2;
    tileSize = GetScreenHeight() * 0.7 / 4;
    tileMargin = 5;

    Texture downArrow = LoadTexture("downbutton.png");

    mainPanel = new Panel(horizontalMargin, verticalMargin, GetScreenWidth() - 2 * horizontalMargin, GetScreenHeight() - 2 * verticalMargin);
    startLabel = new Label("Start", horizontalMargin, 60, WHITE, SegoeUI, 90);
    downButton = new UserControl("Down", downArrow, horizontalMargin, GetScreenHeight() - 100, 50, 50);
    
    mainPanel->font = SegoeUI;
    mainPage.panels.push_back(mainPanel);
    mainPage.labels.push_back(startLabel);
    mainPage.userControls.push_back(downButton);
}


void UnloadResources()
{
    UnloadFont(SegoeUI);
    for(Panel* panelptr : mainPage.panels){
        for(Tile* tileptr : panelptr->tiles){
            delete tileptr;
        }
        for(ListItem* listItemPtr : panelptr->listItems){
            delete listItemPtr;
        }
        delete panelptr;
    }
    for(Label* labelPtr : mainPage.labels){
        delete labelPtr;
    }
    for (std::pair<std::string, Texture> entry : textureMap) {
        UnloadTexture(entry.second);
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