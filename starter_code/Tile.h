#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

#include <string>

#include "TileCodes.h"

// Color and Unicode escape sequences for printing colored text and Unicode
// symbols in the console

// #define RESET_COLOR "\033[0m"           // Reset color to default
// #define RED_COLOR "\033[31m"            // Red color
// #define ORANGE_COLOR "\u001b[38;5;209m" // Orange color
// #define YELLOW_COLOR "\033[33m"         // Yellow color
// #define GREEN_COLOR "\033[32m"          // Green color
// #define BLUE_COLOR "\033[34m"           // Blue color
// #define PURPLE_COLOR "\033[35m"         // Purple color

// #define CIRCLE_UNICODE "\U000025EF"    // Circle symbol
// #define FOUR_STAR_UNICODE "\U00002726" // Four star symbol
// #define DIAMOND_UNICODE "\U000025C6"   // Diamond symbol
// #define SQUARE_UNICODE "\U000025FC"    // Square symbol
// #define SIX_STAR_UNICODE "\U0001F7CC"  // Six star symbol
// #define CLOVER_UNICODE "\U00002618"    // Clover symbol

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile {
 public:
  Tile(Colour colour, Shape shape);
  ~Tile();

  Colour getColour() const;
  Shape getShape() const;

  // Add toString function declaration
  std::string toString();

  bool isValidTile(Colour colour, Shape shape);

 private:
  Colour colour;
  Shape shape;
};

#endif  // ASSIGN2_TILE_H
