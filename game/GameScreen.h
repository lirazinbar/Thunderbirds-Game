#pragma once

#include "Board.h"
#include "Timer.h"
#include "Ship.h"
#include "Block.h"
#include <string>
#include <fstream>

class GameScreen {
	std::ifstream screenFile;
	std::string screenFileName;
	std::vector<std::string> screenFileNames;
	int screenNumber = 0;
public:
	//Empty Ctor
	GameScreen();
	// Destructor - Closing the screen text file
	~GameScreen() { screenFile.close(); }
	// Return the screen file (ifstream)
	std::ifstream& getScreenFile() { return screenFile; }
	// Return the screen number
	int getScreenNumber() { return screenNumber; }
	// Set the file position to the beginning
	void returnToFileBeginning();
	// Choose a screen to play by entering the file name,
	//or pick the first screen as default
	void chooseScreen();
	// Prints a message to the screen after encountering a file related error
	// Exit to main menu
	void printFileRelatedMessage(const char* errorMessage) const;
	// Get the screen file name from the player
	void getScreenFileNameFromPlayer();
	// Opens the next screen text file in lexicographical order (1, 2, 3,...)
	void openNextScreenFile();
	// Load the file into the SingeGame object
	// Reads the header and the board
	void load(Board& board, Timer& timer);
	// Read the header of the file
	void readHeader(Timer& timer);
	// Read the board in the file
	void readBoard(Board& board);
};

