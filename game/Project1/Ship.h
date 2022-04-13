#pragma once

#include <iostream>
#include <vector>
#include "Utils.h"
#include "Board.h"

enum class ShipsIndex { BIG_SHIP, SMALL_SHIP };

class Ship {
	char ch;
	int size;
	bool hasReachedEndPoint = false;
	int blockSizeCapacity;
	Board* pBoard = nullptr;
	std::vector<Point> points;
	int topPointsIndexes[2];
public:
	// Ctor
	Ship(char _ch, int _size, Board* _pBoard, int _blockSizeCapacity);
	// Return the points vector of the ship
	std::vector<Point> getPoints() const { return points; }
	// Return the size of the ship
	int getSize() const { return size; }
	// Return the char of the ship
	char getChar() const { return ch; }
	// Return if the ship has reached end point or not
	bool endPointStatus() { return hasReachedEndPoint; }
	// Set the "reached end point" status of the ship
	void setHasReachedEndPoint(bool _hasReachedEndPoint) { hasReachedEndPoint = _hasReachedEndPoint; }
	//Return what is the maximum block size the ship can move/hold
	int getBlockSizeCapacity() { return blockSizeCapacity; }
	// Move the ship according to dirx, diry
	void move(int difx, int dify);
	// Draw the ship on screen
	void drawOnScreen() const;
	// Delete the ship from screen
	void deleteFromScreen() const;
	// Checks if the ship includes the Pint p
	bool isShipIncludesPoint(Point p);
	// Checking which of the ship points are the top layer points and save their indexes
	void setTopPoints();
	// Return vector with the top points of the ship
	std::vector<Point> getAboveShipPoints();
};

