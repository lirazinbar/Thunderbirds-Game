#pragma once

#include "GameScreen.h"
#include "Utils.h"

typedef struct mode {
	GameMode main;
	GameMode secondary = GameMode::REGULAR;
} Mode;

class Game {
	static int livesCount;
	static bool keepPlaying;
	static bool gameWon;
	static Mode mode;
public:
	// Run the whole game program
	void run(int argc, char* argv[]);
	// Determine which game mode the player chose
	void setGameMode(int argc, char* argv[]);
	// Return the main game mode
	static GameMode getMainGameMode() { return mode.main; }
	// Return the secondary game mode
	static GameMode getSecondaryGameMode() { return mode.secondary; }
	// This function runs the while game, until exit, losing or winning
	void play();
	// Return the current lives count
	static int getLivesCount() { return livesCount; }
	// Decrese the live count by 1
	static void decreseLives() { Game::livesCount -= 1; }
	// Return true if the game should keep going
	static bool getKeepPlayingSatus() { return Game::keepPlaying; }
	// Set the "keepPlaying" falg to false
	static void stopPlaying() { Game::keepPlaying = false; }
	// Return the current game winning status
	static bool getGameWinningStatus() { return gameWon; }
	// Set the game winning status (True or false)
	static void setGameWinningStatus(bool gameWinningStatus) { Game::gameWon = gameWinningStatus;}
	// Check if the user lost the game
	bool isGameLost() const;
};