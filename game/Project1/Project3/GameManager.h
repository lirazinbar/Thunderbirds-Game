#pragma once

#include "Ship.h"
#include "Point.h"
#include "Timer.h"
#include "Legend.h"

class GameManager {
	Board* pBoard = nullptr;
	Legend legend{ pBoard };
	Timer timer;
	int activeShip = int(ShipsIndex::BIG_SHIP);
	int livesCount = 3;
	bool gamePaused = false;
public:
	GameManager(Board* _pBoard) : pBoard(_pBoard) { legend.setBoardPointer(_pBoard); };
	int getActiveShip() const { return activeShip; }
	const Legend& getLegend() { return legend; }
	int getLives() const { return livesCount; }
	void decreseLives() { livesCount -= 1; }
	Timer& getTimer() { return timer; }
	void changePauseMode() {};
	void changeActiveShip(ShipsIndex ship) { activeShip = int(ship); };

};