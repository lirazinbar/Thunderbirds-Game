#pragma once

#include "Board.h"
#include "Timer.h"
#include "Ship.h"
#include "Block.h"
#include "Files.h"
#include "Record.h"
#include <string>
#include <fstream>

class Record;

class GameScreen {
	std::fstream screenFile;
	std::vector<std::string> screenFileNames;
	int screenNumber = 0;
public:
	//Ctor which get the suffix of the files to be opened.
	GameScreen() { getRelevantFiles(screenFileNames, FileSuffix::SCREEN); }
	// Destructor - Closing the screen text file
	~GameScreen() { screenFile.close(); }
	// Return the screen file (ifstream)
	std::fstream& getScreenFile() { return screenFile; }
	// Return the screen number
	int getScreenNumber() { return screenNumber; }
	// Choose a screen to play by entering the file name,
	//or pick the first screen as default
	void chooseScreen(Record& gameRecord);
	// Set the first saved screen as the first screen to play
	void chooseFirstSavedScreen(Record& gameRecord);
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

