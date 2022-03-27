#pragma once

#include "Board.h"
#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include "Timer.h"
#include "Color.h"
#include "Game.h"

class SingleGame {
	bool gameWon = false;
	bool keepPlaying = true;
	Board board;
	Timer timer;
	Ship ships[2] = { {char(BoardSymbols::BIG_SHIP), 4, &board, 6}, {char(BoardSymbols::SMALL_SHIP), 2, &board, 2} }; // Index 0 is big ship and 1 is small ship
	int activeShip = int(ShipsIndex::BIG_SHIP);
	Block blocks[2] = { {'$', 4, &board}, {'%', 2, &board} };
	int blocksAmount = 2;
	int livesCount;
	//Color color;
	int dirx = 0;
	int diry = 0;
public:
	SingleGame(int _livesCount): livesCount(_livesCount) { board.print(activeShip, timer.getTimeLeft(), livesCount); };
	~SingleGame();
	void play();
	void assignKey(char& key);
	void changeActiveShip(ShipsIndex _activeShip);
	bool isTimeRanOut();
	void pauseGame();
	bool isGameWon();
	void moveShip();
	bool checkBlocksAdjacentShip(std::vector<Point> adjacentShipPoints);
	void moveBlocksVertically();
	bool areCharsInVec(std::vector<Point> points, char* charsArr, int size);
	bool isArrayIncludesChar(char* arr, int size, char ch);
	bool isBlockCanMove(int blockIndex);
	bool checkShipPushBlock(std::vector<Point> points);
	void checkBlockFallsOnShip(std::vector<Point> points, int blockSize);
};