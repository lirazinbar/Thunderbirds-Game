#pragma once

#include "Board.h"
#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include "Timer.h"
#include "Legend.h"

class Game {
	Board board;
	Ship ships[2] = { {char(BoardSymbols::BIG_SHIP), 4, &board}, {char(BoardSymbols::SMALL_SHIP), 2, &board} }; // Index 0 is big ship and 1 is small ship
	Block block = {'$', 3, &board};
	Legend legend{ &board };
	Timer timer;
	int activeShip = int(ShipsIndex::BIG_SHIP);
	int livesCount = 3;
	int dirx = 0;
	int diry = 0;
	bool keepPlaying = true;
public:
	void run();
	void assignKey(char& key);
	void changeActiveShip(ShipsIndex _activeShip);
	void decreseLives() { livesCount -= 1; }
	int checkTime();
	void pauseGame();
	void resetScreen();
	void resetShips();
	//void resetBlocks();
	bool checkGameLose();
	void checkGameWin();
};