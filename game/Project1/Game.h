#pragma once

#include "Board.h"
#include "Point.h"
#include "Ship.h"

enum class ShipsIndex { BIG_SHIP, SMALL_SHIP };

class Game {
	Board board;
	
	Ship ships[2] = { {'#', 4, &board}, {'@', 2, &board} }; // Index 0 is big ship and index 1 is small ship
	//Point blocks[2];
	int activeShip = int(ShipsIndex::BIG_SHIP);
	int dirx = 0;
	int diry = 0;
public:
	void run();
	void assignKey(char key, bool& keepRuning);
};