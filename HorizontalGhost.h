#pragma once
#include "Ghost.h"
#include "Point.h"
#include "Utils.h"

class HorizontalGhost : public Ghost {
	int dirx = 1;

public:
	HorizontalGhost(const Point& _point, int _dirx = 1) : Ghost(_point), dirx(_dirx) {}
	// Changes the dir to the opposite
	void changeDir() override { dirx = -1 * dirx; }
	// Set the dir to the given dir
	void setDir(int _dirx, int _diry) override { dirx = _dirx; }
	void setDir(int _dir) override { if(_dir != 0) dirx = _dir; }
	// Moves the ghost
	void move() { Ghost::moveGhost(dirx, 0); }
	// Returns the point after moving
	Point getNextPointToMove() { return Ghost::calcNextPointToMove(dirx, 0); }
	// Returns the dir(to the file saving - 0)
	int getDir() override { return 0; }
	GhostsTypes getType() override {
		return GhostsTypes::HORIZONTAL_GHOST_TYPE;
	}
};
