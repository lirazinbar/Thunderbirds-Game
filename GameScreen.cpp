#include "GameScreen.h"
#include "Utils.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <filesystem>

void GameScreen::chooseScreen(Record& gameRecord) {
	bool isValid = false;
	char playerChoice;
	
	clrscr();
	// Load mode, read the steps and result files
	if (Game::getMainGameMode() == GameMode::LOAD) {
		gameRecord.getRecordFiles();
		if (Game::getKeepPlayingSatus()) {
			chooseFirstSavedScreen(gameRecord);
			gameRecord.readSavedGameScreen();
		}
	}
	else {
		std::cout << "(1) Play the first screen" << std::endl;
		std::cout << "(2) Play a specific screen" << std::endl;
		while (!isValid) {
			if (_kbhit()) {
				playerChoice = _getch();
				if (playerChoice == Keys::PlayFirstScreen) {
					isValid = true;
					screenNumber = 1;
				}
				else if (playerChoice == Keys::PlaySpecificScreen) {
					isValid = true;
					getScreenFileNameFromPlayer();
				}
				// If the file name the player entered is valid
				if (Game::getKeepPlayingSatus()) {
					openFile(screenFile, screenFileNames[screenNumber - 1], OpenMode::READ);
				}
			}
		}
	}
}

void GameScreen::chooseFirstSavedScreen(Record& gameRecord) {
	bool found = false;
	// The first saved file
	std::string stepsFileName = gameRecord.getRecordFilesNames()[0];
	std::string stepsFilePrefix;
	
	int prefixLen = stepsFileName.find(".");
	stepsFilePrefix = stepsFileName.substr(0, prefixLen);
	for (int i = 0; i < screenFileNames.size() && !found; i++) {
		std::string screenFilePrefix = screenFileNames[i].substr(0, prefixLen);
		if (stepsFilePrefix.compare(screenFilePrefix) == 0) {
			found = true;
			screenNumber = i + 1;
			gameRecord.setSavedFileIndex(i);
			openFile(screenFile, screenFileNames[i], OpenMode::READ);
		}
	}
}

void GameScreen::getScreenFileNameFromPlayer() {
	bool found = false;
	std::string screenFileName;

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
		printErrorFileRelatedMessage(true, "Error! The file doesn't exist. Exiting to main menu...");
	}
}

void GameScreen::openNextScreenFile() {
	screenNumber++;
	screenFile.close();
	// In case the player finished the last screen
	if (screenNumber > screenFileNames.size()) {
		printWinMessage(true);
		Game::stopPlaying();
	}
	else {
		openFile(screenFile, screenFileNames[screenNumber - 1], OpenMode::READ);
		Game::setGameWinningStatus(false);
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
