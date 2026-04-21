#include "raylib.h" 
#include "resource_dir.h"
#include "graphic-objects.h"

extern Color windowsPurple;
extern Color defaultBackgroundColor;

int changeBackgroundColor(Color newColor);
void InitialAnimation();
void FinalAnimation();
void Render();
void LoadResources();
void UnloadResources();

extern int horizontalMargin, verticalMargin;
extern Panel* mainPanel;
extern Panel* appsPanel;
extern Panel* searchPanel;
extern Page mainPage;
extern Page appsPage;
extern Page searchPage;

extern TextBox* queryBox;

extern Font SegoeUI;