#include "raylib.h"
#include <string>
#include <vector>
#include "graphic-objects.h"
#include <cmath>
#include <map>
#include <iostream>

float tileSize;
float tileMargin;
int fontSize = 20;

std::map<std::string, Texture> textureMap;

bool Tile::isLeftClicked() {
    Vector2 mousePosition = GetMousePosition();
    float screenX = this->offsetX + tileMargin + tileSize * this->gridX;
    float screenY = this->offsetY + tileMargin + tileSize * this->gridY;
    return CheckCollisionPointRec(mousePosition, (Rectangle){ screenX, screenY, this->width * tileSize - 2 * tileMargin, this->height * tileSize - 2 * tileMargin }) && IsMouseButtonDown(MOUSE_LEFT_BUTTON);
}

void Tile::Draw(float offsetX, float offsetY) {
    this->offsetX = offsetX;
    this->offsetY = offsetY;

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
    if(backgroundColor.a > 0){
        DrawRectangle(offsetX, offsetY, this->width, this->height, backgroundColor);
    }

    for (Tile* tileptr : tiles) {
        tileptr->Draw(offsetX + this->x, offsetY + this->y);
    }
    for (ListItem* listItemPtr : listItems) {
        listItemPtr->Draw(offsetX + this->x, offsetY + this->y);
    }

    if(isScrollable){

        this->x += GetMouseWheelMove()*50;
        
        if(GetMouseWheelMove() == 0){
            lastScrollValue -= lastScrollValue/3;
            this->x += lastScrollValue*75;
        } else {
            lastScrollValue = GetMouseWheelMove();
        }

        if(this->x > (this->notScrolledX)){
            this->x = this->notScrolledX; 
            lastScrollValue = 0;
            return;
        }else if(this->x + this->furthestPointX * tileSize < this->width + this->notScrolledX){
            this->x = this->notScrolledX +  this->width - this->furthestPointX * tileSize; 
            lastScrollValue = 0;
            return;
        }
        
    }
}


void UserControl::Draw(float offsetX, float offsetY)
{
    this->offsetX = offsetX;
    this->offsetY = offsetY;

    Color tint = (Color){ 255, 255, 255, 255 * opacity };
    DrawRectangle(this->x + offsetX, this->y + offsetY, this->width, this->height, backgroundColor);
    DrawTextureEx((this->icon), (Vector2){ this->x + offsetX, this->y + offsetY }, 0, width/icon.width ,tint);
}

bool UserControl::clicked(){
    float screenX = this->x + offsetX;
    float screenY = this->y + offsetY;
    return CheckCollisionPointRec(GetMousePosition(), (Rectangle){ screenX, screenY, this->width, this->height }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool UserControl::isMouseOver(){
    float screenX = this->x + offsetX;
    float screenY = this->y + offsetY;
    return CheckCollisionPointRec(GetMousePosition(), (Rectangle){ screenX, screenY, this->width, this->height });
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

void ListItem::Draw(float offsetx, float offsety)
{
    this->offsetX = offsetx;
    this->offsetY = offsety;

    Color color = (Color){ backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a * opacity * this->parentPanel->opacity };
    Color text = (Color){ textColor.r, textColor.g, textColor.b, textColor.a * opacity * this->parentPanel->opacity };

    float halfTileSize = tileSize;
    float screenX = offsetx + this->gridX * tileSize;
    float screenY = offsety + this->gridY * tileSize * 2 / 3 ;

    std::string tempLabel = this->label.c_str();

    while(MeasureTextEx(this->parentPanel->font, tempLabel.c_str(), 30, 1).x > this->width * tileSize - 20 *tileMargin) {
        tempLabel.erase(tempLabel.length() - 1);
    }

    if(tempLabel.compare(this->label)) tempLabel.append("...");    

    DrawRectangle(screenX, screenY, this->width * halfTileSize, this->height * halfTileSize/1.5, color);

    if (this->icon.id != 0)
    {
        float iconSize;
        if(this->width > this->height){
            iconSize = (this->height)/1.5f;
        } else {
            iconSize = (this->width)/1.5f;
        }
        DrawTextureEx(this->icon, (Vector2){ screenX + 2 * tileMargin, screenY + (this->height / 2) - iconSize / 2 }, 0, iconSize / 1000, (Color){ 255, 255, 255, 255 * opacity });
        DrawTextEx(this->parentPanel->font, tempLabel.c_str(), (Vector2){  screenX + 15 * tileMargin, screenY + this->height * halfTileSize / 3 - 15 }, 30, 1, text);
    } else {
        DrawTextEx(this->parentPanel->font, tempLabel.c_str(), (Vector2){  screenX + 2 * tileMargin, screenY + this->height * halfTileSize / 3 - 15 }, 30, 1, text);
    }
}


bool ListItem::clicked()
{
    float screenX = this->offsetX + this->gridX * tileSize;
    float screenY = this->offsetY + this->gridY * tileSize * 2 / 3;
    return CheckCollisionPointRec(GetMousePosition(), (Rectangle){ screenX, screenY, this->width * tileSize, this->height * tileSize * 2 / 3 }) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

bool ListItem::isMouseOver()
{
    float screenX = this->offsetX + this->gridX * tileSize;
    float screenY = this->offsetY + this->gridY * tileSize * 2 / 3;
    return CheckCollisionPointRec(GetMousePosition(), (Rectangle){ screenX, screenY, this->width * tileSize, this->height * tileSize * 2 / 3 });
}
