#pragma once

#include "Point.h"
#include "Board.h"

enum class LegendElementsXLocation { ACTIVE_SHIP = 13, TIMER = 36, LIVES = 53 }; // The X locations of the legend values

class Board;

class Legend {
	Point legendLocation{ 3, 1 };  // Default location
	Board* pBoard = nullptr;
public:
	Legend(Board* _pBoard);
	void setBoardPointer(Board* _pBoard) { pBoard = _pBoard; }
	const Point& getLegendLocation() const { return legendLocation; }
	void print(int activeShip, int timeLeft, int livesCount) const;
	void printActiveShip(int activeShip) const;
	void printLives(int livesCount) const;
	void printTimer(int timeLeft) const;
};