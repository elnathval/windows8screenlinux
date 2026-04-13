#include "raylib.h"
#include <string>
#include <vector>
#include "graphic-objects.h"
#include <cmath>
#include <map>

float tileSize;
float tileMargin;
int fontSize = 20;

std::map<std::string, Texture> textureMap;

bool Tile::isLeftClicked() {
    Vector2 mousePosition = GetMousePosition();
    float screenX = this->parentPanel->x + tileMargin + tileSize * this->gridX;
    float screenY = this->parentPanel->y + tileMargin + tileSize * this->gridY;
    return CheckCollisionPointRec(mousePosition, (Rectangle){ screenX, screenY, this->width * tileSize - 2 * tileMargin, this->height * tileSize - 2 * tileMargin }) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}

void Tile::Draw(float offsetX, float offsetY) {
    float panelX = tileMargin + tileSize * this->gridX;
    float screenX = panelX + offsetX;
    float panelY = tileMargin + tileSize * this->gridY;
    float screenY = panelY + offsetY;
    float tileWidth = this->width * tileSize - 2 * tileMargin;
    float tileHeight = this->height * tileSize - 2 * tileMargin;
    Color color = (Color){ backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a * opacity * parentPanel->opacity };
    Color textColor = (Color){ 255, 255, 255, 255 * opacity * parentPanel->opacity };
    
    DrawRectangle(screenX, screenY, tileWidth, tileHeight, color);
    DrawTextEx(this->parentPanel->font, this->label.c_str(), (Vector2){ screenX + tileMargin, screenY + tileHeight - tileMargin - fontSize }, fontSize, 1, textColor);

    if (textureMap.find(this->label) != textureMap.end())
    {
        float iconSize;
        if(this->width > this->height){
            iconSize = (tileHeight)/1.5f;
        } else {
            iconSize = (tileWidth)/1.5f;
        }
        DrawTextureEx(textureMap[this->label], (Vector2){ screenX + (tileWidth / 2) - iconSize / 2, screenY + (tileHeight / 2) - iconSize / 2 }, 0, iconSize / 1000, (Color){ 255, 255, 255, 255 * opacity * parentPanel->opacity });
    }
}


void Panel::Draw(float offsetX, float offsetY) {

    for (Tile* tileptr : tiles) {
        tileptr->Draw(offsetX + this->x, offsetY + this->y);
    }
}


void UserControl::Draw(float offsetX, float offsetY)
{
    Color tint = (Color){ 255, 255, 255, 255 * opacity };
    DrawTextureEx((this->icon), (Vector2){ this->x + offsetX, this->y + offsetY }, 0, width/icon.width ,tint);
}

void Page::Draw()
{
    for (Panel* panelptr : panels) {
        panelptr->Draw(this->x, this->y);
    }
    for (UserControl* userControlPtr : userControls) {
        userControlPtr->Draw(this->x, this->y);
    }
    for (Label* labelPtr : labels) {
        labelPtr->Draw(this->x, this->y);
    }
}

void Label::Draw(float offsetX, float offsetY)
{
    Color textColor = (Color){ color.r, color.g, color.b, color.a * opacity };
    DrawTextEx(this->font, this->text.c_str(), (Vector2){ this->x + offsetX, this->y + offsetY }, this->fontSize, 1, textColor);
}
