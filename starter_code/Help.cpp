#include "Help.h"
#include <iostream>

void Help::displayMainMenuHelp() {
    std::cout << "\nCommands:\n"
              << "By pressing 1 followed by the enter key, the program will start a New Game of Qwirkle\n"
              << "By pressing 2 followed by the enter key, the program will Load Game that has been previously saved\n"
              << "By pressing 3 followed by the enter key, the program will shows information about the students who created the QWIRKLE game.\n"
              << "By pressing 4 followed by the enter key, the program will end.\n"
              << std::endl;
}

void Help::displayNamingHelp() {
    std::cout << "\nName help:\n" 
              << "\n You are asked to enter your name. You can enter any name you like, but it must be at least 1 character long.\n"
              << "\n If you enter a name that is less than 1 character long, the game will prompt you to enter a name again, \n"
              << "\n it also has to be capitals and only letters, numbers are not allowed" 
              << std::endl;
}

void Help::displaySelectActionHelp() {
    std::cout << "\nSelect Action Help:\n" 
              << "\n This menu allows you to choose out of 4 options, each with the corresponding number to input."
              << "\n 1. Place Tile: This option allows you to place a tile on the board. You will be prompted to enter the row and column of the board where you want to place the tile, and the tile you want to place. If the move is valid, the tile will be placed on the board. If the move is invalid, you will be prompted to enter the move again."
              << "\n 2. Replace Tile: This option allows you to replace a tile in your hand with a tile from the bag. You will be prompted to enter the tile you want to replace, and the tile you want to replace it with. If the move is valid, the tile will be replaced. If the move is invalid, you will be prompted to enter the move again."
              << "\n 3. Save Game: This option allows you to save the current state of the game to a file. You will be prompted to enter the name of the file you want to save the game to. If the file already exists, you will be prompted to enter the name of the file again."
              << "\n 4. Load Game: This option allows you to load a game from a file. You will be prompted to enter the name of the file you want to load the game from. If the file does not exist, you will be prompted to enter the name of the file again."
              << std::endl;
}

void Help::displayPlaceTileHelp() {
    std::cout << "\nPlace Tile Help:\n" 
    << "This option allows you to place a tile on the board. \n" 
    << "You will be prompted to enter the row and column of the board where you want to place the tile, \n"
    << "and the tile you want to place. If the move is valid, the tile will be placed on the board. \n"
    << "If the move is invalid, you will be prompted to enter the move again. \n"
    << "example input: place tile at A1 \n"
    << "Where tile is the tile in your hand and A1 is a location on the board you want to place your tile. \n" 
    << std::endl;
}

void Help::displayReplaceTileHelp() {
    std::cout << "\nReplace Tile Help:\n" 
    << "This option allows you to replace a tile in your hand with a tile from the bag. \n"
    << "You will be prompted to enter the tile you want to replace, and the tile you want to replace it with. \n"
    << "If the move is valid, the tile will be replaced. If the move is invalid, you will be prompted to enter the move again. \n"
    << "example input: replace tile \n"
    << "Where tile is the tile in your hand you would like to replace. \n"
    << std::endl;
}

void Help::displaySaveGameHelp() {
    std::cout << "\nSave Game Help:\n" 
    << "This option allows you to save the current state of the game to a file. \n"
    << "You will be prompted to enter the name of the file you want to save the game to. \n"
    << "If the file already exists, you will be prompted to enter the name of the file again. \n"
    << "example input: file1 \n"
    << "Where file1 is the name of the file you would like. No need to add a file extension \n"
    << std::endl;
}

void Help::displayLoadGameHelp() {
    std::cout << "\nLoad Game Help:\n"
    << "This option allows you to load a game from a file. \n"
    << "You will be prompted to enter the name of the file you want to load the game from. \n"
    << "If the file does not exist, you will be prompted to enter the name of the file again. \n"
    << "example input: file1 \n"
    << "Where file1 is the name of the file you would like to load. It looks for the file in the tests folder. \n"
    << std::endl;
}






