#include "LinkedList.h"
#include <iostream>
#include <vector>
using std::cout;
using std::endl;
using std::cin;
using std::string;
using std::vector;
#define EXIT_SUCCESS    0


void displayMenu();
bool isValidPlayerName(const string& name);
void displayStudentInformation();

// Define a structure to represent student information
struct Student {
    string name;
    string studentID;
    string email;
};


int main(void) {
   LinkedList* list = new LinkedList();
   delete list;

    //std::cout << "TODO: Implement Qwirkle!" << std::endl;
    //2.1 Launch
   cout << "Welcome to Qwirkle!" << endl;
   cout << "-----------------------" << endl;

    int choice = 0;
    bool quit = false;

    while (!quit) {
        displayMenu();
        cout << "> ";
        cin >> choice;

        if (choice == 1) {
            cout << "\nStarting a New Game" << endl;

            // Player 1
            string player1;
            do {
                cout << "\nEnter a name for player 1 (uppercase characters only): ";
                cin >> player1;
            } while (!isValidPlayerName(player1));

            // Player 2
            string player2;
            do {
                cout << "\nEnter a name for player 2 (uppercase characters only): ";
                cin >> player2;
            } while (!isValidPlayerName(player2));

            cout << "\nLet's Play!" << endl;
            /**  Add code to proceed with normal gameplay
2.3.10 Special Operation: Starting a New Game 
When a new game is started, a special sequence of operations must be conducted: 
1. Create the ordering for the tile bag 
2. Set up the initial player hands 
3. Start with an empty board, with player 1 as the starting player 
You will need to devise your own algorithm to “shuffle” the bag of tiles to create a “random” initial order. This 
is left up to your own invention. The lectures will talk about randomness is C++ programs. 
Then the initial tiles are added to the player’s hands. 6 tiles are drawn from the tile bag and placed in the 1st 
player’s hand. Then 6 tiles are drawn from the tile bag and placed in the 2nd player’s hand. 
Finally, the board starts with no tiles placed, so that when displayed, it should be empty. 


            **/      


        } else if (choice == 2) {
            cout << "Loading Game..." << endl;
            // Add code for loading a game
        } else if (choice == 3) {
            
            displayStudentInformation();
            
        } else if (choice == 4) {
            cout << "Quitting the game. Goodbye!" << endl;
            quit = true;
        } else {
            cout << "Invalid choice. Please enter a valid option." << endl;
        }
    }

    return EXIT_SUCCESS;
}

void displayMenu() {
   cout << "\nMenu" << endl;
   cout << "1. New Game" << endl;
   cout << "2. Load Game" << endl;
   cout << "3. Credits (Show student information)" << endl;
   cout << "4. Quit" << endl;
}


// Function to check if a player name is valid
bool isValidPlayerName(const string& name) {
    for (char c : name) {
      //check if we can use this
        if (!isupper(c) || !isalpha(c)) {
            cout << "Invalid name. Please enter uppercase letters only." << endl;
            return false;
        }
    }
    return true;
}

//2.2.3 Credits - Need members to add their details 
void displayStudentInformation() {
    
   cout << "--------------------------------------" << endl;
    // Hardcoded information for 4 students
    cout << "\nName: Michael Moon" << endl;
    cout << "Student ID: S12345678" << endl;
    cout << "Email: john.doe@example.com" << endl;

    cout << "\nName: Alexander Cowan" << endl;
    cout << "Student ID: S23456789" << endl;
    cout << "Email: jane.smith@example.com" << endl;

    cout << "\nName: Michael Whyte" << endl;
    cout << "Student ID: s3851481" << endl;
    cout << "Email: S3851481@student.rmit.edu.au" << endl;

    cout << "\nName: Morgan Cassar" << endl;
    cout << "Student ID: S45678901" << endl;
    cout << "Email: alice.williams@example.com" << endl;
    cout << "--------------------------------------" << endl;
    cout << "\n<Main Menu>" << endl;
}