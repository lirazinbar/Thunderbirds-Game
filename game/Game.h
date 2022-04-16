#pragma once

#include "GameScreen.h"

class Game {
	static int livesCount;
	static bool keepPlaying;
	static bool gameWon;
public:
	// Run the whole game program
	void run();
	// This function runs the while game, until exit, losing or winning
	void play();
	// Return the current lives count
	static int getLivesCount() { return livesCount; }
	// Decrese the live count by 1
	static void decreseLives() { Game::livesCount -= 1; }
	// Set the "keepPlaying" falg to false
	static void stopPlaying() { Game::keepPlaying = false; }
	// Return the current game winning status
	static bool getGameWinningStatus() { return gameWon; }
	// Set the game winning status (True or false)
	static void setGameWinningStatus(bool gameWinningStatus) { Game::gameWon = gameWinningStatus;}
	// Check if the user lost the game
	bool isGameLost() const;
};