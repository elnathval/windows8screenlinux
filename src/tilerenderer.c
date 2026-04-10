#include "raylib.h"
#include "rendering.h"
#include <stdio.h>

struct ProgramRectangle {
    int x;
    int y;
    int width;
    int height;
    Color backgroundColor;
    char *label;
    char *command;
};

struct Tile
{
    int x;
    int y;
    int width;
    int height;
    Color backgroundColor;
    char *label;
    char *command;
};

struct ProgramRectangle appArray[10] = {
    {0,0,2,1, WHITE, "Desktop", ""},
    {0,1,1,1, LIGHTGRAY, "Chrome", "google-chrome"}
};

    
struct Tile tiles[10];

void GetTiles(){ 

    for (int i = 0; i < 10; i++)
    {
        struct ProgramRectangle rect = appArray[i];
        int tileX = horizontalMargin + tileSize * rect.x + tileMargin;
        int tileY = verticalMargin + tileSize * rect.y + tileMargin;

        tiles[i] = (struct Tile){tileX, tileY, rect.width * (tileSize - 2 * tileMargin), rect.height * (tileSize - 2 * tileMargin), rect.backgroundColor, rect.label, rect.command};
    }

}

void RenderTile(struct Tile tile, Font font)
{
    DrawRectangle(tile.x, tile.y, tile.width, tile.height, tile.backgroundColor);
    DrawTextEx(font, tile.label, (Vector2){tile.x + 10, tile.y + 10}, 20, 2, WHITE);
}