#pragma once

#include "Board.h"
#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include "Timer.h"
#include "Legend.h"
#include "Color.h"

class Game {
	Board board;
	Ship ships[2] = { {char(BoardSymbols::BIG_SHIP), 4, &board, 6}, {char(BoardSymbols::SMALL_SHIP), 2, &board, 2} }; // Index 0 is big ship and 1 is small ship
	Block blocks[2] = { {'$', 4, &board}, {'%', 2, &board} };
	int blocksAmount = 2;
	Legend legend{ &board };
	Timer timer;
	//Color color;
	int activeShip = int(ShipsIndex::BIG_SHIP);
	int livesCount = 3;
	int dirx = 0;
	int diry = 0;
	bool keepPlaying = true;
public:
	void run();
	void assignKey(char& key);
	void changeActiveShip(ShipsIndex _activeShip);
	void decreseLives() { livesCount -= 1; resetScreen();}
	int checkTime();
	void pauseGame();
	void resetScreen();
	void resetShips();
	void resetBlocks();
	bool checkGameLose();
	void checkGameWin();
	void moveShip();
	void moveBlocksVertically();
	bool areCharsInVec(std::vector<Point> points, char* charsArr, int size);
	bool isArrayIncludesChar(char* arr, int size, char ch);
	bool isBlockCanMove(int blockIndex);
	bool checkShipPushBlock(std::vector<Point> points);
	void checkBlockFallsOnShip(std::vector<Point> points, int blockSize);
	void resetGame(); 
};