#include "Tile.h"
#include "TileCodes.h"
#include <iostream>
// Constructor implementation
#include "Tile.h"
#include "TileCodes.h"

#include "Tile.h"
#include <iostream>

Tile::Tile()
{
}

Tile::~Tile()
{
}

Tile::Tile(Colour colour, Shape shape)
{
    this->colour = colour;
    this->shape = shape;
}

bool Tile::equals(Colour colour, Shape shape)
{
    return (this->colour == colour && this->shape == shape);
}

std::string Tile::toString()
{
    std::string retval;
    retval.push_back(colour);        // Push the colour character onto the string
    retval += std::to_string(shape); // Concatenate the shape integer
    return retval;
}
