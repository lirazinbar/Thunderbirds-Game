#include "Game.h"
#include "singleGame.h"
#include "Utils.h"

// Initialize static boolean and int for Game and SingleGame 
bool Game::keepPlaying;
int Game::livesCount;

void Game::run() {
	char userChoice = 0;
	hide_cursor();
	
	while (userChoice != Keys::ESC) {
		printMainMenu(userChoice);
		if (userChoice == '1') {
			play();
		}
		else if (userChoice == '8') {
			//color.setColorMode(presentInstructions());
		}
	}
}

void Game::play() {
	Game::keepPlaying = true;
	Game::livesCount = 3;

	while (!isGameLost() && keepPlaying) {
		SingleGame(livesCount).play();
	}
}

bool Game::isGameLost() {
	if (livesCount == 0) {
		printLoseMessage();
		return true;
	}
	return false;
}