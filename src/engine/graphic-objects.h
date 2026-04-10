#include "raylib.h"
#include <string>
#include <vector>

extern float tileSize;
extern float tileMargin;

class Tile {
public:
    int gridX;
    int gridY;
    int width;
    int height;
    Color backgroundColor;
    std::string label;
    std::string command;
    //A tile is defined by its position in the grid, its dimension (in grid units), its background color, a label to display on it, and a command to execute when clicked
    Tile(int x, int y, int width, int height, Color backgroundColor, std::string label, std::string command);
    bool isLeftClicked();
    void changeColor(Color newColor);
    int realX;
    int realY;
    
};

class Panel {
public:
    float x;
    float y;
    float width;
    float height;
    std::vector<Tile*> tiles;
    Font font;
    Panel(); // default constructor
    //This x, y, width and height of the panel are in screen coordinates, not grid coordinates. The panel will be responsible for rendering the tiles within it based on their grid coordinates and the panel's position and size.
    Panel(float x, float y, float width, float height);
    //This x and y of the panel are in screen coordinates, not grid coordinates. The panel will be responsible for rendering the tiles within it based on their grid coordinates and the panel's position.
    Panel(float x, float y);
    void add(Tile* tileptr);
    void Draw();
    void Draw(float offset);
    void Move(float newX, float newY);
};