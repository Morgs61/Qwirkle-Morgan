#include "Tile.h"
#include "TileCodes.h"
#include "LinkedList.h"
#include <iostream>
// Constructor implementation
Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape)
{
    /*
     *
     * TODO: Some bullshittery happening here. Ignore this for now.
     * */

    /* if (!isValidTile(colour, shape)) {
       // log the tile colour and shape
       std::cout << "Invalid tile colour and shape: " << colour << shape << std::endl;
       throw std::invalid_argument("Invalid tile");
   }*/
}

bool Tile::isValidTile(Colour colour, Shape shape)
{
    // Define valid colours and shapes directly in the function
    Colour validColours[] = {RED, ORANGE, YELLOW, GREEN, BLUE, PURPLE};
    Shape validShapes[] = {CIRCLE, STAR_4, DIAMOND, SQUARE, STAR_6, CLOVER};

    // Check if the colour and shape are valid
    for (size_t i = 0; i < sizeof(validColours) / sizeof(validColours[0]); ++i)
    {
        if (colour == validColours[i] && shape == validShapes[i])
        {
            return true;
        }
    }
    return false;
}

Colour Tile::getColour() const
{
    return colour;
}

Shape Tile::getShape() const
{
    return shape;
}
// Destructor implementation (if needed)
// Add missing include statement

Tile::~Tile()
{
    // Any destruction if needed
}

std::string Tile::toString()
{
    std::string retval = colour + std::to_string(shape);
    return retval;
}