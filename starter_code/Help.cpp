#include "Help.h"
#include <iostream>

void Help::displaySelectActionHelp() {
    std::cout << "\ndisplaySelectActionHelp:\n" << std::endl;
}

void Help::displaySaveGameHelp() {
    std::cout << "\ndisplaySaveGameHelp:\n" << std::endl;
}

void Help::displayReplaceTileHelp() {
    std::cout << "\ndisplayReplaceTileHelp:\n" << std::endl;
}

void Help::displayPlaceTileHelp() {
    std::cout << "\ndisplayPlaceTileHelp:\n" << std::endl;
}

void Help::displayMainMenuHelp() {
    std::cout << "\nCommands:\n"
              << "By pressing 1 followed by the enter key, the program will start a New Game of Qwirkle\n"
              << "By pressing 2 followed by the enter key, the program will Load Game that has been previously saved\n"
              << "By pressing 3 followed by the enter key, the program will shows information about the students who created the QWIRKLE game.\n"
              << "By pressing 4 followed by the enter key, the program will end.\n"
              << std::endl;
}

void Help::displayNewGameMenuHelp() {
    std::cout << "\nNew Game Menu Options:\n" << std::endl;
}
