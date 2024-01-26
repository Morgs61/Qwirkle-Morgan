#include "Tile.h"
#include "TileCodes.h"
#include <iostream>
// Constructor implementation
Tile::Tile(Color color, Shape shape) : color(color), shape(shape)
{
}

// Destructor implementation (if needed)
// Add missing include statement

Tile::~Tile()
{
}

#include <vector>

void printTileBag(const std::vector<Tile> &tileBag)
{
    std::cout << "Tile Bag: ";
    for (const Tile &tile : tileBag)
    {
        std::cout << tile.color << tile.shape << " ";
    }
    std::cout << "\nNumber of tiles in bag: " << tileBag.size() << std::endl;
}

std::string Tile::toString()
{
    // Combine color and shape into a string representation
    std::string tileString = color + std::to_string(shape);
    return tileString;
}

std::string Tile::toPrettierString()
{
    std::string retval;

    // Map the shape to its corresponding constant
    std::string shapeStr;
    switch (shape)
    {
    case CIRCLE:
        shapeStr = "CIRCLE";
        break;
    case STAR_4:
        shapeStr = "STAR_4";
        break;
    case DIAMOND:
        shapeStr = "DIAMOND";
        break;
    case SQUARE:
        shapeStr = "SQUARE";
        break;
    case STAR_6:
        shapeStr = "STAR_6";
        break;
    case CLOVER:
        shapeStr = "CLOVER";
        break;
    }

    // Map the color to its corresponding constant
    std::string colorStr;
    switch (color)
    {
    case RED:
        colorStr = "RED";
        break;
    case ORANGE:
        colorStr = "ORANGE";
        break;
    case YELLOW:
        colorStr = "YELLOW";
        break;
    case GREEN:
        colorStr = "GREEN";
        break;
    case BLUE:
        colorStr = "BLUE";
        break;
    case PURPLE:
        colorStr = "PURPLE";
        break;
    }

    // Build the result string
    retval = colorStr + " " + shapeStr + " " + std::to_string(shape);

    return retval;
}