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
	Ship(char _ch, int _size, Board* _pBoard, int _blockSizeCapacity);
	void resetLocatin() { points = pBoard->getPoints(ch, size); }
	std::vector<Point> getPoints() const { return points; }
	int getSize() const { return size; }
	char getChar() const { return ch; }
	void move(int difx, int dify);
	void drawOnScreen() const;
	void deleteFromScreen() const;
	bool endPointStatus() { return hasReachedEndPoint; }
	void setHasReachedEndPoint(bool _hasReachedEndPoint) { hasReachedEndPoint = _hasReachedEndPoint; }
	bool isShipIncludesPoint(Point p);
	int getBlockSizeCapacity() { return blockSizeCapacity; }
	void setTopPoints();
	std::vector<Point> getAboveShipPoints();
};

