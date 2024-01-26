
#ifndef ASSIGN2_TILE_H
#define ASSIGN2_TILE_H

// Define a Colour type
typedef char Colour;

// Define a Shape type
typedef int Shape;

class Tile
{
public:
   // Constructor
   Tile(Colour colour, Shape shape);

   // Destructor
   ~Tile();

   Colour colour;
   Shape shape;
   // bool equals(Tile* other);
   // //bool operator==(const Tile& other) const;
   // bool operator!=(const Tile& other) const;

   std::string toString();

   std::string toPrettierString();
};

#endif // ASSIGN2_TILE_H
