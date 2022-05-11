#pragma once
#include "Ghost.h"
#include "Point.h"

class VerticalGhost : public Ghost {
	int diry = 1;

public:
	VerticalGhost(const Point& _point, int _diry = 1) : Ghost(_point), diry(_diry) {};
	// Changes the dir to the opposite
	void changeDir() override { diry = -1 * diry; }
	// Set the dir to the given dir
	void setDir(int _diry) override { diry = _diry; }
	// Moves the ghost
	void move() { Ghost::moveGhost(0, diry); }
	// Returns the point after moving
	Point getNextPointToMove() { return Ghost::calcNextPointToMove(0, diry); }
};

