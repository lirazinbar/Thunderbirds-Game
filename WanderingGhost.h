#pragma once
#include "Ghost.h"
#include "Point.h"
#include "Utils.h"

class WanderingGhost : public Ghost {
	int dirx = 0;
	int diry = 1;
	int stepsCounter = 2;

public:
	WanderingGhost(const Point& _point) : Ghost(_point) {}
	// Changes the dir to the opposite
	void changeDir() override;
	// Set the dir to the given dir
	void setDir(int _dirx, int _diry) override { dirx = _dirx; diry = _diry; }
	void setDir(int _dir) override;
	// Moves the ghost
	void move();
	// Returns the point after moving
	Point getNextPointToMove() { return Ghost::calcNextPointToMove(dirx, diry); }
	// Returns the dir
	int getDir() override;
	GhostsTypes getType() override {
		return GhostsTypes::WANDERING_GHOST_TYPE;
	}
};