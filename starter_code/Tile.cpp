#include "Tile.h"
#include "TileCodes.h"
#include <iostream>
// Constructor implementation
Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape)
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
        std::cout << tile.colour << tile.shape << " ";
    }
    std::cout << "\nNumber of tiles in bag: " << tileBag.size() << std::endl;
}

std::string Tile::toString()
{
    // Combine colour and shape into a string representation
    std::string tileString = colour + std::to_string(shape);
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

    // Map the colour to its corresponding constant
    std::string colourStr;
    switch (colour)
    {
    case RED:
        colourStr = "RED";
        break;
    case ORANGE:
        colourStr = "ORANGE";
        break;
    case YELLOW:
        colourStr = "YELLOW";
        break;
    case GREEN:
        colourStr = "GREEN";
        break;
    case BLUE:
        colourStr = "BLUE";
        break;
    case PURPLE:
        colourStr = "PURPLE";
        break;
    }

    // Build the result string
    retval = colourStr + " " + shapeStr + " " + std::to_string(shape);

    return retval;
}