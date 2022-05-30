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
	// // Load + Silent modes
	//if (argc >= 2 && argc <= 3 && strcmp(argv[1], RecordArgumants::LOAD) == 0) {
	//	Game::mode.main = GameMode::LOAD;
	//	if (argc == 3 && strcmp(argv[2], RecordArgumants::SILENT) == 0) {
	//		Game::mode.secondary = GameMode::SILENT;
	//	}
	//}
	//// Save mode
	//else if (argc == 2 && strcmp(argv[1], RecordArgumants::SAVE) == 0)
	//	Game::mode.main = GameMode::SAVE;
	//// Regular mode
	//else if (argc == 1)
	//	Game::mode.main = GameMode::REGULAR;
	//else
	//	printInvalidCmdInput();
	Game::mode.main = GameMode::LOAD;

}

void Game::play() {
	Game::keepPlaying = true;
	Game::gameWon = false;
	Game::livesCount = 3;
	GameScreen screen;
	Record gameRecord;
	int pointOfTime = 0;
		
	// If there at least one relevant file in the directory
	if (Game::keepPlaying) {
		screen.chooseScreen(gameRecord);
		while (!isGameLost() && Game::keepPlaying) {
			pointOfTime = SingleGame(livesCount, screen).play(gameRecord);
			if (pointOfTime == -1) {
				Game::keepPlaying = false;
			}
			returnToFileBeginning(screen.getScreenFile());
			if (Game::gameWon == true) {
				// gameRecord.setScreenFinishTimePoint(pointOfTime);
				Game::livesCount = 3; // Reset lives
				screen.openNextScreenFile();
				if (Game::mode.main != GameMode::REGULAR)
					gameRecord.openNextSavedGameScreen(screen.getScreenNumber()-1);
			}
		}
		// If you didn't finish last screen
		if (Game::gameWon == false && Game::mode.main == GameMode::SAVE) {
			// gameRecord.addDeathPointOfTime(pointOfTime);
			gameRecord.writeSavedGameScreen(screen.getScreenNumber());
		}
	}
}

bool Game::isGameLost() const {
	return (livesCount == 0);
}