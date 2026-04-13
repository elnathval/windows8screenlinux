#include "raylib.h"
#include <string>
#include <vector>
#include <map>

extern float tileSize;
extern float tileMargin;
extern std::map<std::string, Texture> textureMap;

class Panel;

class UserControl;

class Label;

class Page {
public:
    float x, y;
    std::vector<Panel*> panels;
    std::vector<UserControl*> userControls;
    std::vector<Label*> labels;
    std::string Title;
    Page(std::string title, float x, float y) {
        this->Title = title;
        this->x = x;
        this->y = y;
    }
    void Draw();
    void Move(float newX, float newY){
        this->x = newX;
        this->y = newY;
    };
};

class Tile {
public:
    int gridX, gridY;
    int width, height;
    float offsetX, offsetY;
    Color backgroundColor;
    std::string label, command;
    Panel* parentPanel;
    float opacity = 1.0f;

    //A tile is defined by its position in the grid, its dimension (in grid units), its background color, a label to display on it, and a command to execute when clicked
    Tile(int x, int y, int width, int height, Color backgroundColor, std::string label, std::string command) {
        this->gridX = x;
        this->gridY = y;
        this->width = width;
        this->height = height;
        this->backgroundColor = backgroundColor;
        this->label = label;
        this->command = command;
    };
    bool isLeftClicked();
    void changeColor(Color newColor) {
        this->backgroundColor = newColor;
    };
    void Draw(float offsetX, float offsetY);
};

class UserControl {
public:
    std::string name;
    Texture icon;
    float x, y;
    float width, height; 
    float offsetX, offsetY;
    float opacity = 1.0f;
    UserControl(std::string name, Texture icon, int x, int y, int width, int height) {
        this->name = name;
        this->icon = icon;
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    }
    void clicked();
    void Draw(float offsetX, float offsetY);
};

class ListItem {
public:
    std::string label;
    Texture icon;
    std::string command;
    ListItem(std::string label, Texture icon, std::string command){
        this->label = label;
        this->icon = icon;
        this->command = command;
    };
    void Draw(float offsetx, float offsety);
};

class Panel {
public:
    float x, y, width, height;
    float offsetX, offsetY;
    float opacity = 1.0f;
    std::vector<Tile*> tiles;
    std::vector<ListItem*> listItems;
    Font font;
    Page* parentPage;

    //This x, y, width and height of the panel are in screen coordinates, not grid coordinates. The panel will be responsible for rendering the tiles within it based on their grid coordinates and the panel's position and size.
    Panel(float x, float y, float width, float height){
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
    };
    //This x and y of the panel are in screen coordinates, not grid coordinates. The panel will be responsible for rendering the tiles within it based on their grid coordinates and the panel's position.
    Panel(float x, float y){
        this->x = x;
        this->y = y;
    };
    void add(Tile* tileptr){
        tileptr->parentPanel = this;
        this->tiles.push_back(tileptr);
    };
    void Draw(float offsetX, float offsetY);
    void Move(float newX, float newY){
        this->x = newX;
        this->y = newY;
    };
};

class Label {
public:
    std::string text;
    float x, y;
    Color color;
    Font font;
    float opacity = 1.0f;
    int fontSize = 90;
    Label(std::string text, float x, float y, Color color, Font font, int fontSize) {
        this->text = text;
        this->x = x;
        this->y = y;
        this->color = color;
        this->font = font;
        this->fontSize = fontSize;
    };
    void Draw(float offsetX, float offsetY);
};