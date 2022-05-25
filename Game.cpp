#include "Game.h"
#include "singleGame.h"
#include "Utils.h"
#include "Record.h"
#include "Files.h"
#include <fstream>
#include <string>

// Initialize static variables for Game and SingleGame 
bool Game::keepPlaying = true;
bool Game::gameWon;
int Game::livesCount;
Mode Game::mode;

void Game::run(int argc, char* argv[]) {
	char userChoice = 0;
	bool silentMode = false;

	hide_cursor();
	setGameMode(argc , argv);
	// If input is valid
	if (Game::keepPlaying == true) {
		// Load mode
		if (Game::mode.main == GameMode::LOAD)
			play();
		// Regular or save modes
		else {
			while (userChoice != Keys::Exit) {
				printMainMenu(userChoice);
				if (userChoice == Keys::StartNewGame) {
					play();
				}
				else if (userChoice == Keys::Instructions) {
					Color::setColorMode(presentInstructions());
				}
			}
			printExitMessage();
		}
	}
}

void Game::setGameMode(int argc, char* argv[]) {
	// Load + Silent modes
	if (argc >= 2 && argc <= 3 && strcmp(argv[1], RecordArgumants::LOAD) == 0) {
		Game::mode.main = GameMode::LOAD;
		if (argc == 3 && strcmp(argv[2], RecordArgumants::SILENT) == 0)
			Game::mode.secondary = GameMode::SILENT;
	}
	// Save mode
	else if (argc == 2 && strcmp(argv[1], RecordArgumants::SAVE) == 0)
		Game::mode.main = GameMode::SAVE;
	// Regular mode
	else if (argc == 1)
		Game::mode.main = GameMode::REGULAR;
	else
		printInvalidCmdInput();
}

void Game::play() {
	Game::keepPlaying = true;
	Game::gameWon = false;
	Game::livesCount = 3;
	GameScreen screen;
	Record gameRecord;
		
	// If there at least one relevant file in the directory
	if (Game::keepPlaying) {
		screen.chooseScreen(gameRecord);
		while (!isGameLost() && Game::keepPlaying) {
			SingleGame(livesCount, screen).play(gameRecord);
			returnToFileBeginning(screen.getScreenFile());
			if (Game::gameWon == true) {
				Game::livesCount = 3; // Reset lives
				screen.openNextScreenFile();
				if (Game::mode.main != GameMode::REGULAR)
					gameRecord.openNextSavedGameScreen();
			}
		}
		// If you didn't finish last screen
		if (Game::gameWon == false && Game::mode.main == GameMode::SAVE)
			gameRecord.writeSavedGameScreen();
	}
}

bool Game::isGameLost() const {
	return (livesCount == 0);
}