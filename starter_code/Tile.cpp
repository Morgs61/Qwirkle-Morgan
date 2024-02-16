#include <iostream>

#include "LinkedList.h"
#include "Tile.h"
#include "TileCodes.h"
// Constructor implementation
Tile::Tile(Colour colour, Shape shape) : colour(colour), shape(shape) {}

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

Colour Tile::getColour() const { return colour; }

Shape Tile::getShape() const { return shape; }
// Destructor implementation (if needed)
Tile::~Tile()
{
  // Any destruction if needed
}

std::string Tile::toString()
{
  std::string retval = colour + std::to_string(shape);
  return retval;
}

std::string Tile::toUnicode()
{
  std::string retval;

  std::string shapeUnicode;

  // Determine the Unicode symbol corresponding to the shape
  if (shape == CIRCLE)
  {
    shapeUnicode = CIRCLE_UNICODE;
  }
  else if (shape == STAR_4)
  {
    shapeUnicode = FOUR_STAR_UNICODE;
  }
  else if (shape == DIAMOND)
  {
    shapeUnicode = DIAMOND_UNICODE;
  }
  else if (shape == SQUARE)
  {
    shapeUnicode = SQUARE_UNICODE;
  }
  else if (shape == STAR_6)
  {
    shapeUnicode = SIX_STAR_UNICODE;
  }
  else if (shape == CLOVER)
  {
    shapeUnicode = CLOVER_UNICODE;
  }
  else
  {
    shapeUnicode = "";
  }

  // Determine the ANSI escape code corresponding to the color
  std::string colorCode;
  if (colour == 'R')
  {
    colorCode = RED_COLOR;
  }
  else if (colour == 'O')
  {
    colorCode = ORANGE_COLOR;
  }
  else if (colour == 'Y')
  {
    colorCode = YELLOW_COLOR;
  }
  else if (colour == 'G')
  {
    colorCode = GREEN_COLOR;
  }
  else if (colour == 'B')
  {
    colorCode = BLUE_COLOR;
  }
  else if (colour == 'P')
  {
    colorCode = PURPLE_COLOR;
  }
  else
  {
    colorCode = "";
  }

  // Construct the string representation of the tile
  retval = colorCode + shapeUnicode + RESET_COLOR + " ";

  return retval;
}