#include "raylib.h"
#include <string>
#include <vector>
#include "graphic-objects.h"
#include <cmath>

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
    }
}
void Panel::Draw(float offset) {    //FOr the start animation
    for (Tile* tileptr : tiles) {
        Tile tile = *tileptr;
        float screenX = tile.realX;
        float screenY = tile.realY;

        DrawRectangle(screenX + offset * 2 * tileSize, screenY + offset * tileSize, tile.width * tileSize - 2 * tileMargin, tile.height * tileSize - 2 * tileMargin, (Color){ tile.backgroundColor.r, tile.backgroundColor.g, tile.backgroundColor.b, tile.backgroundColor.a * (1 - 2 * offset) });
        DrawTextEx(this->font, tile.label.c_str(), (Vector2){ screenX + tileMargin + offset * 2 * tileSize, (screenY + tile.height * tileSize - 3 * tileMargin - fontSize) + offset * tileSize }, fontSize, 1, (Color){ 255, 255, 255, 255 * (1 - 2 * offset) });
    }
}