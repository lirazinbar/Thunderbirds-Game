#include "Game.h"
#include "singleGame.h"
#include "Utils.h"
#include <fstream>
#include <string>

// Initialize static boolean and int for Game and SingleGame 
bool Game::keepPlaying;
bool Game::gameWon;
int Game::livesCount;

void Game::run() {
	char userChoice = 0;
	hide_cursor();
	
	while (userChoice != '9') {
		printMainMenu(userChoice);
		if (userChoice == '1') {
			play();
		}
		else if (userChoice == '8') {
			Color::setColorMode(presentInstructions());
		}
	}
	printExitMessage();
}

void Game::play() {
	Game::keepPlaying = true;
	Game::gameWon = false;
	Game::livesCount = 3;
	GameScreen screen;
	std::string line;
	
	screen.chooseScreen();
	while (!isGameLost() && keepPlaying) {
		SingleGame(livesCount, screen).play();
		screen.returnToFileBeginning();
		if (Game::gameWon == true) {
			Game::livesCount = 3; // Reset lives
			Game::gameWon = false;
			screen.openNextScreenFile();
		}
	}
}

bool Game::isGameLost() const {
	return (livesCount == 0);
}