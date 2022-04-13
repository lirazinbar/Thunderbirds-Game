#pragma once

#include "Board.h"
#include "Timer.h"
#include "Ship.h"
#include "Block.h"
#include <string>
#include <fstream>

class GameScreen {
	std::ifstream screenFile;
	// Default file name, the first screen
	std::string screenFileName = "tb1.screen.txt";
	int screenNumber;
public:
	// Destructor - Closing the screen text file
	~GameScreen() { screenFile.close(); }
	// Set the file position to the beginning
	void returnToFileBeginning();
	// Return the screen file (ifstream)
	std::ifstream& getScreenFile() { return screenFile; }
	// Return the screen number
	int getScreenNumber() { return screenNumber; }
	// Choose a screen to play by entering the file name,
	//or pick the first screen as default
	void chooseScreen();
	// Seraches and return the screen file nubmer according to the file txt name
	int searchScreenNumber();
	// Opens the next screen text file in lexicographical order (1, 2, 3,...)
	void openNextScreenFile();
	// Changes the file name according to the current screen number
	void changeFileName();
	// Checking if the file opens properly. Exiting the current game if not
	// Default 0 to allow function call without parameters
	void checkFileOpening(char playerChoice);
	// Load the file into the SingeGame object
	// Reads the header and the board
	void load(Board& board, Timer& timer);
	// Read the header of the file
	void readHeader(Timer& timer);
	// Read the board in the file
	void readBoard(Board& board);
};

