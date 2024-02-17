#include <algorithm>
#include <iostream>
#include <iostream> // Include for std::std::cout, std::endl
#include <set>
#include <vector> // Include for std::vector

#include "Board.h"

#define COLUMN_MAX 26
#define COLUMN_MIN 1
#define ROW_MAX 25
#define ROW_MIN 0

// contains uppercase letters A to Z
std::string labels[COLUMN_MAX];

Board::Board()
{
  for (int ch = 'A'; ch <= 'Z'; ch++)
  {
    labels[ch - 'A'] = ch;
  }
  board = std::vector<Tile *>(ROWS * COLS, nullptr);
}
bool checkTilePlacement(const std::vector<std::vector<Tile *>> &board, int row,
                        int col);

// Declare fixed size of board here
int BOARD_SIZE = COLUMN_MAX;

Board::~Board()
{
  for (auto tile : board)
  {
    if (tile != nullptr)
    {
      delete tile;
    }
  }
}

std::vector<Tile *> &Board::getBoard() { return board; }

void Board::displayBoard()
{
  // Print the header rows
  for (int i = 0; i < 2; i++)
  {
    for (int j = 0; j < COLUMN_MAX; j++)
    {
      // Print column indices and separators
      if (i == 0 && j == 0)
      {
        std::cout << "   " << j << "  ";
      }
      else if (i == 0 && j < 10)
      {
        std::cout << j << "  ";
      }
      else if (i == 0 && j > 9)
      {
        std::cout << j << " ";
      }
      else if (i == 1 && j == 0)
      {
        std::cout << "  -"
                  << "--";
      }
      else if (i == 1 && j == COLUMN_MAX - 1)
      {
        std::cout << "----";
      }
      else if (i == 1)
      {
        std::cout << "---";
      }
    }
    std::cout << std::endl;
  }

  // Print the board content
  for (int i = 0; i < ROWS; i++)
  {
    std::cout << labels[i] << " "; // Print row labels
    for (int j = 0; j < ROWS; ++j)
    {
      // Check if a tile exists at the current position
      if (board[i * COLS + j] != nullptr)
      {
        std::string tileString = board[i * COLS + j]->toUnicode();
        std::cout << "|" << tileString; // Print the tile's string representation
      }
      else
      {
        std::cout << "|  "; // Print empty space for missing tile
      }
    }
    std::cout << "|" << std::endl; // Close the last cell and end the row
  }
}

void Board::placeTile(Tile *tile, int row, int col)
{
  if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
  {
    board[row * COLS + col] = tile;
  }
}

Tile *Board::getTileAt(int row, int col)
{
  if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
  {
    return board[row * COLS + col];
  }
  return nullptr;
}

std::string Board::getBoardState()
{
  std::string stateString = "";
  for (int i = 0; i < ROWS; i++)
  {
    for (int j = 0; j < COLS; ++j)
    {
      if (board[i * COLS + j] != nullptr)
      {
        stateString += board[i * COLS + j]->toString() + "@" + labels[i] +
                       std::to_string(j) + ", ";
      }
    }
  }
  if (!stateString.empty())
  {
    // Remove the last space and comma
    stateString.pop_back();
    stateString.pop_back();
  }
  return stateString;
}

bool Board::hasTileAt(int row, int col)
{
  if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
  {
    return board[row * COLS + col] != nullptr;
  }
  return false;
}

size_t Board::size() const
{
  return board.size(); // Assuming board is your vector of vectors
}

int Board::getSize()
{
  // return the size of the board
  return board.size();
}
// Function to check surrounding tiles for a tile
bool checkSurroundingTiles(const std::vector<std::vector<Tile *>> &board,
                           int row, int col)
{
  // Check if tile is on the edge of the board
  if (row == 0 || row == ROW_MAX - 1 || col == 0 || col == COLUMN_MAX - 1)
  {
    return true;
  }
  // Check if tile is surrounded by other tiles
  else if (board[row - 1][col] != nullptr || board[row + 1][col] != nullptr ||
           board[row][col - 1] != nullptr || board[row][col + 1] != nullptr)
  {
    return true;
  }
  else
  {
    return false;
  }
}

bool Board::checkSurroundingTilesMatch(int row, int col, Tile *tile)
{
  // Get the board from the Board object
  std::vector<Tile *> boardVector = board;
  std::vector<std::vector<Tile *>> board2D(ROWS,
                                           std::vector<Tile *>(COLS, nullptr));
  for (int i = 0; i < ROWS; ++i)
  {
    for (int j = 0; j < COLS; ++j)
    {
      board2D[i][j] = boardVector[i * COLS + j];
    }
  }

  // Check if board is empty, allowing first tile placement anywhere
  bool isBoardEmpty = std::all_of(
      board2D.begin(), board2D.end(), [](const std::vector<Tile *> &boardRow)
      { return std::all_of(boardRow.begin(), boardRow.end(),
                           [](const Tile *tile)
                           { return tile == nullptr; }); });

  if (isBoardEmpty)
  {
    std::cout << "Board is empty" << std::endl;
    return true;
  }

  // Check existing checks for adjacent tiles
  bool hasNeighbor = checkTilePlacement(board2D, row, col);
  if (!hasNeighbor)
  {
    std::cout << "Tile must be placed next to another tile" << std::endl;
    return false;
  }

  // Check along the row within a limited range
  bool rowMatch = true;
  for (int i = col - 1; i >= 0 && board2D[row][i] != nullptr && rowMatch; --i)
  {
    if (board2D[row][i]->getColour() != tile->getColour() &&
        board2D[row][i]->getShape() != tile->getShape())
    {
      rowMatch = false;
      std::cout << "Tile does not match row values" << std::endl;
    }
  }
  for (int i = col + 1;
       i < BOARD_SIZE && board2D[row][i] != nullptr && rowMatch; ++i)
  {
    if (board2D[row][i]->getColour() != tile->getColour() &&
        board2D[row][i]->getShape() != tile->getShape())
    {
      rowMatch = false;
      std::cout << "Tile does not match row values" << std::endl;
    }
  }

  // Check along the column within a limited range
  bool colMatch = true;
  for (int i = row - 1; i >= 0 && board2D[i][col] != nullptr && colMatch; --i)
  {
    if (board2D[i][col]->getColour() != tile->getColour() &&
        board2D[i][col]->getShape() != tile->getShape())
    {
      colMatch = false;
      std::cout << "Tile does not match column values" << std::endl;
    }
  }
  for (int i = row + 1;
       i < BOARD_SIZE && board2D[i][col] != nullptr && colMatch; ++i)
  {
    if (board2D[i][col]->getColour() != tile->getColour() &&
        board2D[i][col]->getShape() != tile->getShape())
    {
      colMatch = false;
      std::cout << "Tile does not match column values" << std::endl;
    }
  }

  // Check for duplicate tile in the row
  for (int i = col - 1; i >= 0 && board2D[row][i] != nullptr; --i)
  {
    if (board2D[row][i]->getColour() == tile->getColour() &&
        board2D[row][i]->getShape() == tile->getShape())
    {
      std::cout << "Duplicate tile found in row, invalid placement"
                << std::endl;
      return false;
    }
  }
  for (int i = col + 1; i < BOARD_SIZE && board2D[row][i] != nullptr; ++i)
  {
    if (board2D[row][i]->getColour() == tile->getColour() &&
        board2D[row][i]->getShape() == tile->getShape())
    {
      std::cout << "Duplicate tile found in row, invalid placement"
                << std::endl;
      return false;
    }
  }

  // Check for duplicate tile in the column
  for (int i = row - 1; i >= 0 && board2D[i][col] != nullptr; --i)
  {
    if (board2D[i][col]->getColour() == tile->getColour() &&
        board2D[i][col]->getShape() == tile->getShape())
    {
      std::cout << "Duplicate tile found in column, invalid placement"
                << std::endl;
      return false;
    }
  }
  for (int i = row + 1; i < BOARD_SIZE && board2D[i][col] != nullptr; ++i)
  {
    if (board2D[i][col]->getColour() == tile->getColour() &&
        board2D[i][col]->getShape() == tile->getShape())
    {
      std::cout << "Duplicate tile found in column, invalid placement"
                << std::endl;
      return false;
    }
  }

  return rowMatch && colMatch && hasNeighbor;
}

// function to make sure the tile is placed next to another tile
bool Board::checkTilePlacement(const std::vector<std::vector<Tile *>> &board,
                               int row, int col)
{
  // Check if any neighboring positions have a tile
  bool hasNeighbor = false;

  // Check above
  if (row > 0 && board[row - 1][col] != nullptr)
  {
    hasNeighbor = true;
  }

  // Check below
  if (row < BOARD_SIZE - 1 && board[row + 1][col] != nullptr)
  {
    hasNeighbor = true;
  }

  // Check left
  if (col > 0 && board[row][col - 1] != nullptr)
  {
    hasNeighbor = true;
  }

  // Check right
  if (col < BOARD_SIZE - 1 && board[row][col + 1] != nullptr)
  {
    hasNeighbor = true;
  }

  return hasNeighbor;
}

bool checkSameTypeTiles(const std::vector<Tile *> &tilesToPlace,
                        const std::vector<std::pair<int, int>> &positions)
{
  if (tilesToPlace.size() < 2)
  {
    // If there is only one tile, it is considered a valid move
    return true;
  }
  char baseColor = tilesToPlace[0]->getColour();
  int baseShape = tilesToPlace[0]->getShape();
  int baseRow = positions[0].first;
  int baseColumn = positions[0].second;

  for (size_t i = 1; i < tilesToPlace.size(); ++i)
  {
    // Check that all conditions are met for each tile
    if ((tilesToPlace[i]->getColour() != baseColor &&
         tilesToPlace[i]->getShape() != baseShape) ||
        (positions[i].first != baseRow && positions[i].second != baseColumn))
    {
      return false; // Tiles in the move have different color, shape, or
                    // they don't share the same column/row
    }
  }
  return true; // All tiles in the move have the same color, shape, and share
               // the same column or row
}

bool Board::checkSameTypeTiles(
    const std::vector<Tile *> &tilesToPlace,
    const std::vector<std::pair<int, int>> &positions)
{
  if (tilesToPlace.size() < 2)
  {
    // If there is only one tile, it is considered a valid move
    return true;
  }
  char baseColor = tilesToPlace[0]->getColour();
  int baseShape = tilesToPlace[0]->getShape();
  int baseRow = positions[0].first;
  int baseColumn = positions[0].second;

  for (size_t i = 1; i < tilesToPlace.size(); ++i)
  {
    // Check that all conditions are met for each tile
    if ((tilesToPlace[i]->getColour() != baseColor &&
         tilesToPlace[i]->getShape() != baseShape) ||
        (positions[i].first != baseRow && positions[i].second != baseColumn))
    {
      return false; // Tiles in the move have different color, shape, or
                    // they don't share the same column/row
    }
  }
  return true; // All tiles in the move have the same color, shape, and share
               // the same column or row
}

void Board::setTileAtPosition(int row, int col, Tile *tile)
{
  // Check if the row and column are within the board boundaries
  if (row >= 0 && row < ROWS && col >= 0 && col < COLS)
  {
    // Place the tile at the specified position on the board
    board[row * COLS + col] = tile;
  }
  else
  {
    // Print an error message if the position is out of bounds
    std::cout << "Error: Position (" << row << ", " << col
              << ") is out of bounds." << std::endl;
  }
}

int Board::calculateScore(const std::vector<Tile *> &tilesToPlace,
                          const std::vector<std::pair<int, int>> &positions)
{
  int totalScore = 0;
  bool qwirkleHorizontalDetected = false; // Flag to check for QWIRKLE
  bool qwirkleVerticalDetected = false;   // Flag to check for QWIRKLE

  // Keep track of positions of tiles that have already been scored in this
  // move
  std::set<std::pair<int, int>> scoredPositions;

  // Score each tile placement individually
  for (size_t i = 0; i < tilesToPlace.size(); ++i)
  {
    int row = positions[i].first;
    int col = positions[i].second;

    // If this position has already been scored in this move, skip it
    if (scoredPositions.count({row, col}) == 0)
    {
      // Temporarily place tile for scoring
      board[row * COLS + col] = tilesToPlace[i];

      // Score horizontally and vertically
      int scoreHorizontal = 1;
      int scoreVertical = 1;

      // Check left
      for (int j = col - 1; j >= 0 && board[row * COLS + j] != nullptr; --j)
      {
        scoreHorizontal++;
        scoredPositions.insert({row, j}); // Mark this position as scored
      }
      // Check right
      for (int j = col + 1; j < COLS && board[row * COLS + j] != nullptr; ++j)
      {
        scoreHorizontal++;
        scoredPositions.insert({row, j}); // Mark this position as scored
      }
      // Check up
      for (int j = row - 1; j >= 0 && board[j * COLS + col] != nullptr; --j)
      {
        scoreVertical++;
        scoredPositions.insert({j, col}); // Mark this position as scored
      }
      // Check down
      for (int j = row + 1; j < ROWS && board[j * COLS + col] != nullptr; ++j)
      {
        scoreVertical++;
        scoredPositions.insert({j, col}); // Mark this position as scored
      }

      // If tile doesn't form a new sequence, score for that direction is
      // 0 (excluding the tile itself)
      if (scoreHorizontal > 1)
      {
        totalScore += scoreHorizontal;
      }
      if (scoreVertical > 1)
      {
        totalScore += scoreVertical;
      }
      // Check for QWIRKLE horizontally
      if (scoreHorizontal == 6)
      {
        qwirkleHorizontalDetected = true;
      }
      // Check for QWIRKLE vertically
      if (scoreVertical == 6)
      {
        qwirkleVerticalDetected = true;
      }
      // Remove the tile after scoring
      board[row * COLS + col] = nullptr;
    }
  }

  // If QWIRKLE is detected, add a 6-point bonus
  if (qwirkleHorizontalDetected)
  {
    totalScore += 6;
    std::cout << "you made a QWIRKLE in a row!" << std::endl;
  }
  if (qwirkleVerticalDetected)
  {
    totalScore += 6;
    std::cout << "you made a QWIRKLE in a column!" << std::endl;
  }

  // Restore tiles placed for an accurate game state
  for (size_t i = 0; i < tilesToPlace.size(); ++i)
  {
    int row = positions[i].first;
    int col = positions[i].second;
    board[row * COLS + col] = tilesToPlace[i];
  }
  if (totalScore == 0)
  {
    totalScore = 1;
  }

  std::cout << "Score for this move: " << totalScore << std::endl;

  return totalScore;
}

// Function to calculate the score based on a pattern on the board
int Board::calculatePatternScore(int row, int col, int deltaX, int deltaY)
{
  // Initialize variables to track the pattern and score
  int patternLength = 0;
  int score = 0;

  // Retrieve the tile at the specified position
  Tile *currentTile = getTileAt(row, col);

  // Check if the current position is empty or if there's no tile at the specified position
  if (currentTile == nullptr)
  {
    return 0; // Return 0 if there's no tile at the specified position
  }

  // Move along the specified direction (deltaX, deltaY) to check the pattern
  bool continueLoop = true;
  while (continueLoop)
  {
    // Update the row and column coordinates based on the direction
    row += deltaY;
    col += deltaX;

    // Retrieve the tile at the new position
    Tile *nextTile = getTileAt(row, col);

    // Check if the next position is empty or if the tile at the next position is different
    if (nextTile == nullptr || !tilesMatch(currentTile, nextTile))
    {
      continueLoop = false;
    }
    else
    {
      // Increment the pattern length and update the current tile
      patternLength++;
      currentTile = nextTile;
    }
  }

  // Calculate the score based on the pattern length
  // This is a simple scoring mechanism, you can adjust it based on your game rules
  if (patternLength >= 2)
  {
    score = patternLength * 2; // Each tile in the pattern contributes 2 points to the score
  }

  return score;
}

// Function to check if two tiles match (you can adjust this according to your Tile class implementation)
bool Board::tilesMatch(Tile *tile1, Tile *tile2)
{
  // Compare the colour and shape of the two tiles
  return (tile1->getColour() == tile2->getColour()) && (tile1->getShape() == tile2->getShape());
}
