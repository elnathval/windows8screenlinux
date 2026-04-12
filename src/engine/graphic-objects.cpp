#include "raylib.h"
#include <string>
#include <vector>
#include "graphic-objects.h"
#include <cmath>
#include <map>

float tileSize;
float tileMargin;
int fontSize = 20;

Tile::Tile(int x, int y, int width, int height, Color backgroundColor, std::string label, std::string command) {
    this->gridX = x;
    this->gridY = y;
    this->width = width;
    this->height = height;
    this->backgroundColor = backgroundColor;
    this->label = label;
    this->command = command;
}

void Tile::changeColor(Color newColor) {
    this->backgroundColor = newColor;
}

bool Tile::isLeftClicked() {
    Vector2 mousePosition = GetMousePosition();
    return CheckCollisionPointRec(mousePosition, (Rectangle){ this->realX, this->realY, this->width * tileSize - 2 * tileMargin, this->height * tileSize - 2 * tileMargin }) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}

std::vector<Texture> textures;
std::map<std::string, Texture> textureMap;

std::map<std::string, ListItem> listItemMap;

ListItem::ListItem(std::string label, Texture icon, std::string command) {
    this->label = label;
    this->icon = icon;
    this->command = command;
}



Panel::Panel() {
    this->x = 0;
    this->y = 0;
    this->width = 0;
    this->height = 0;
}

Panel::Panel(float x, float y, float width, float height) {
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
}

Panel::Panel(float x, float y) {
    this->x = x;
    this->y = y;
}
void Panel::add(Tile* tileptr) {
    tileptr->realX = this->x + tileptr->gridX * tileSize + tileMargin;
    tileptr->realY = this->y + tileptr->gridY * tileSize + tileMargin;
    this->tiles.push_back(tileptr);
}
void Panel::Draw() {
    for (Tile* tileptr : tiles) {
        Tile tile = *tileptr;
        float screenX = tile.realX;
        float screenY = tile.realY;
        
        DrawRectangle(screenX, screenY, tile.width * tileSize - 2 * tileMargin, tile.height * tileSize - 2 * tileMargin, tile.backgroundColor);
        DrawTextEx(this->font, tile.label.c_str(), (Vector2){ screenX + tileMargin, screenY + tile.height * tileSize - 3 * tileMargin - fontSize }, fontSize, 1, WHITE);

        if (textureMap.find(tile.label) != textureMap.end())
        {
            float iconSize;
            if(tile.width > tile.height){
                iconSize = (tile.height * tileSize - 2 * tileMargin)/1.5f;
            } else {
                iconSize = (tile.width * tileSize - 2 * tileMargin)/1.5f;
            }
            DrawTextureEx(textureMap[tile.label], (Vector2){ screenX + (tile.width * tileSize / 2) - iconSize / 2, screenY + (tile.height * tileSize / 2) - iconSize / 2 }, 0, iconSize / 1000,WHITE);
        }
    }
}
void Panel::Draw(float offset) {    //FOr the start animation
    for (Tile* tileptr : tiles) {
        Tile tile = *tileptr;
        float screenX = tile.realX + offset * 2 * tileSize;
        float screenY = tile.realY + offset * tileSize;

        DrawRectangle(screenX, screenY, tile.width * tileSize - 2 * tileMargin, tile.height * tileSize - 2 * tileMargin, (Color){ tile.backgroundColor.r, tile.backgroundColor.g, tile.backgroundColor.b, tile.backgroundColor.a * (1 - 2 * offset) });
        DrawTextEx(this->font, tile.label.c_str(), (Vector2){ screenX + tileMargin, (screenY + tile.height * tileSize - 3 * tileMargin - fontSize)}, fontSize, 1, (Color){ 255, 255, 255, 255 * (1 - 2 * offset) });

        if (textureMap.find(tile.label) != textureMap.end())
        {
            float iconSize;
            if(tile.width > tile.height){
                iconSize = (tile.height * tileSize - 2 * tileMargin)/1.5f;
            } else {
                iconSize = (tile.width * tileSize - 2 * tileMargin)/1.5f;
            }
            DrawTextureEx(textureMap[tile.label], (Vector2){ screenX + (tile.width * tileSize / 2) - iconSize / 2, screenY + (tile.height * tileSize / 2) - iconSize / 2 }, 0, iconSize / 1000,WHITE);
        }
    }
}
