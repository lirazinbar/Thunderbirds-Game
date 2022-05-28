#pragma once
#include "Point.h"
#include "Color.h"

class Ghost {
	Point point;

public:
	// Ctor
	Ghost(const Point& _point) : point(_point) {}
	// Pring the ghost on screen
	void drawOnScreen() const;
	// Move the ghost by the given dirs
	void moveGhost(int dirx, int diry);
	// deletes the ghost from the screen
	void deleteFromScreen() const;
	// Returns the ghost point
	Point& getPoint() { return point; }
	// Returns true if the Ghost point is in the given points vector
	int isGhostExistInPointsVec(const std::vector<Point>& points);

	// Get the next point of the ghost by the given dirs
	Point calcNextPointToMove(int dirx, int diry) { return Point(point.getX() + dirx, point.getY() + diry); }
	virtual Point getNextPointToMove() = 0;
	// Changes the dir to the opposite
	virtual void changeDir() = 0;
	virtual void move() = 0;
	// Set the dir to the given dir
	virtual void setDir(int _dirx, int _diry) = 0;
	virtual void setDir(int _dir) = 0;
	virtual int getDir() = 0;
};