#include "GameScreen.h"
#include "Utils.h"
#include "Game.h"
#include <iostream>
#include <Windows.h>
#include <conio.h>
#include <regex>

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
			if (playerChoice == '1') {
				isValid = true;
				// Default file name, the first screen
			}
			else if (playerChoice == '2') {
				isValid = true;
				clrscr();
				std::cout << "Please enter the screen file name:" << std::endl;
				std::getline(std::cin, screenFileName);
			}
			screenNumber = searchScreenNumber();
			screenFile.open(screenFileName);
		}
	}
	checkFileOpening(playerChoice);
}

int GameScreen::searchScreenNumber() {
	std::regex regexScreenNubmer("[1-9]+");
	std::smatch m;

	std::regex_search(screenFileName, m, regexScreenNubmer);
	return stoi(m.str());
}

void GameScreen::checkFileOpening(char playerChoice = '0') {
	clrscr();
	if (screenFile.fail()) {
		clrscr();
		gotoxy(int(PrintPoints::MESSAGE_X), int(PrintPoints::MESSAGE_Y));
		if (playerChoice == '1') {
			// In case the player chose '1' - default screen, which is the first screen.
			// The files names are in lexicographical order,
			// So we assume there are no screen files in the directory.
			std::cout << "Error! There are no screen files in the directory. Exiting to main menu..." << std::endl;
		}
		else if (playerChoice == '2') {
			// If The file the player chose doesn't exist
			std::cout << "Error! File doesn't exist. Exiting to main menu..." << std::endl;
		}
		else {
			// In case of trying to open next screen file,
			// but there are no screen files left
			std::cout << "Hooray! You finished the last screen and rescued the Egyptologists!" << std::endl;
		}
		Game::stopPlaying();
		// Sleep for 3 seconds
		Sleep(3000);
		clrscr();
	}
}

void GameScreen::openNextScreenFile() {
	screenNumber++;
	changeFileName();
	screenFile.close();
	screenFile.open(screenFileName);
	checkFileOpening();
}

void GameScreen::changeFileName() {
	if (screenNumber < 10) {
		screenFileName.replace(2, 1, std::to_string(screenNumber));
	}
	else {
		screenFileName.replace(2, 2, std::to_string(screenNumber));
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
