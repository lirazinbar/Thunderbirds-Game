#include "GameScreen.h"
#include "Utils.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <regex>
#include <filesystem>

GameScreen::GameScreen() {
	std::filesystem::path pwd = std::filesystem::current_path();
	std::string currentFileName;

	for (auto& file : std::filesystem::directory_iterator(pwd)) {
		currentFileName = file.path().filename().string();
		// Search for all the tb*.screen.txt files in pwd
		if (file.is_regular_file() && currentFileName.starts_with("tb") && currentFileName.ends_with(".screen.txt")) {
			screenFileNames.push_back(currentFileName);
		}
	}
	// If there are no screen files
	if (screenFileNames.size() == 0) {
		printFileRelatedMessage("Error! There are no screen files in the directory. Exiting to main menu...");
	}
	else {
		// Sort the file names in lexicographical order
		std::sort(screenFileNames.begin(), screenFileNames.end());
	}
}

void GameScreen::returnToFileBeginning() {
	screenFile.clear();
	screenFile.seekg(0);
}

void GameScreen::chooseScreen() {
	bool isValid = false;
	char playerChoice;
	
	clrscr();
	std::cout << "(1) Play the first screen" << std::endl;
	std::cout << "(2) Play a specific screen" << std::endl;
	while (!isValid) {
		if (_kbhit()) {
			playerChoice = _getch();
			if (playerChoice == Keys::PlayFirstScreen) {
				isValid = true;
				screenNumber = 1;
				// The first screen
				screenFileName = screenFileNames[screenNumber - 1];
			}
			else if (playerChoice == Keys::PlaySpecificScreen) {
				isValid = true;
				getScreenFileNameFromPlayer();
			}
			// If the file name the player entered is valid
			if (Game::getKeepPlayingSatus()) {
				screenFile.open(screenFileName);
				// If there is a problem opening the file
				if (screenFile.fail()) {
					printFileRelatedMessage("Error! There was a probelm opening the screen file. Exiting to main menu...");
				}
			}
		}
	}
}

void GameScreen::printFileRelatedMessage(const char* errorMessage) const {
	clrscr();
	gotoxy(int(PrintPoints::MESSAGE_X), int(PrintPoints::MESSAGE_Y));
	std::cout << errorMessage << std::endl;
	Game::stopPlaying();
	// Sleep for 3 seconds
	Sleep(3000);
}

void GameScreen::getScreenFileNameFromPlayer() {
	bool found = false;

	clrscr();
	std::cout << "Please enter the screen file name:" << std::endl;
	std::getline(std::cin, screenFileName);

	for (int i = 0; i < screenFileNames.size() && !found; i++) {
		if (screenFileName.compare(screenFileNames[i]) == 0) {
			found = true;
			screenNumber = i + 1;
		}
	}
	// If the file the player chose doesn't exist
	if (found == false) {
		printFileRelatedMessage("Error! The file doesn't exist. Exiting to main menu...");
	}
}

void GameScreen::openNextScreenFile() {
	screenNumber++;
	screenFile.close();
	// In case the player finished the last screen
	if (screenNumber > screenFileNames.size()) {
		printFileRelatedMessage("Hooray! You finished the last screen and rescued the Egyptologists!");
	}
	else {
		screenFile.open(screenFileNames[screenNumber - 1]);
		if (screenFile.fail()) {
			printFileRelatedMessage("Error! There was a probelm opening the screen file. Exiting to main menu...");
		}
	}
}

void GameScreen::load(Board& board, Timer& timer) {
	readHeader(timer);
	readBoard(board);
}

void GameScreen::readHeader(Timer& timer) {
	std::string line;

	// Skip the first two lines, which have info about the header
	screenFile.ignore(256, '\n');
	screenFile.ignore(256, '\n');
	std::getline(screenFile, line);
	// Change from string to number, how much time to screen
	timer.setTimeLeft(atoi(line.c_str()));
	// Skip the empty spcae line that separate the header from the board
	screenFile.ignore(256, '\n');
	//std::getline(screenFile, line);
}

void GameScreen::readBoard(Board& board) {
	std::string line;
	int rowNumber = 0;

	// Read until end of file, one line at a time
	// Copy every line into a 2D char grid - The board
	while (std::getline(screenFile, line)) {
		board.setRow(rowNumber, line.c_str());
		rowNumber++;
	}
}
