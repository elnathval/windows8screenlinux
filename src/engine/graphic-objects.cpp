#include "raylib.h"
#include <string>
#include <vector>
#include "graphic-objects.h"

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
    float screenX = this->gridX * tileSize + tileMargin;
    float screenY = this->gridY * tileSize + tileMargin;
    return CheckCollisionPointRec(mousePosition, (Rectangle){ screenX, screenY, this->width * tileSize - 2 * tileMargin, this->height * tileSize - 2 * tileMargin }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
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
void Panel::add(Tile tile) {
    tile.realX = this->x + tile.gridX * tileSize + tileMargin;
    tile.realY = this->y + tile.gridY * tileSize + tileMargin;
    this->tiles.push_back(tile);
}
void Panel::Draw() {
    for (Tile tile : tiles) {
        float screenX = tile.realX;
        float screenY = tile.realY;
        
        DrawRectangle(screenX, screenY, tile.width * tileSize - 2 * tileMargin, tile.height * tileSize - 2 * tileMargin, tile.backgroundColor);
        DrawTextEx(this->font, tile.label.c_str(), (Vector2){ screenX + tileMargin, screenY + tile.height * tileSize - 3 * tileMargin - fontSize }, fontSize, 1, WHITE);
    }
}