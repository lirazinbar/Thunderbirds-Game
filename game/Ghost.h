#pragma once
#include "Point.h"

class Ghost {
	Point point;

public:
	// Ctor
	Ghost(Point _point) : point(_point) {}
	// Pring the ghost on screen
	void drawOnScreen() const;
	// Move the ghost by the given dirs
	void move(int dirx, int diry);
	// deletes the ghost from the screen
	void deleteFromScreen() const;
	// Get the next point of the ghost by the given dirs
	Point getNextPointToMove(int dirx, int diry) { return Point(point.getX() + dirx, point.getY() + diry); }
	// Returns the ghost point
	Point& getPoint() { return point; }
	// Returns true if the Ghost point is in the given points vector
	int isGhostExistInPointsVec(std::vector<Point> points);
};

