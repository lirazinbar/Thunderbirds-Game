#pragma once
#include "Point.h"

class Ghost {
	Point point;

public:
	Ghost(const Point& _point) : point(_point) {}
	void drawOnScreen() const;
	void move(int dirx, int diry);
	void deleteFromScreen() const;
	Point getNextPointToMove(int dirx, int diry) const { return Point(point.getX() + dirx, point.getY() + diry); }
};

