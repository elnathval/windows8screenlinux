#include "raylib.h"
#include "rendering.h"

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

void GetTiles();

extern struct Tile tiles[10];