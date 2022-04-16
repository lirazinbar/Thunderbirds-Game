#pragma once
#include "Ghost.h"
#include "Point.h"

class HorizontalGhost : public Ghost {
	int dirx = 1;

public:
	HorizontalGhost(Point _point, int _dirx = 1) : Ghost(_point), dirx(_dirx) {}
	void changeDir() { dirx = -1 * dirx; }
	void move() { Ghost::move(dirx, 0); }
	Point getNextPointToMove() { return Ghost::getNextPointToMove(dirx, 0); }
};

