#include "Ship.h"
#include "Point.h"
#include "Board.h"
#include "Utils.h"
#include "Color.h"

Ship::Ship(char _ch, int _size, Board* _pBoard, int _blockSizeCapacity) : ch(_ch), size(_size), pBoard(_pBoard), blockSizeCapacity(_blockSizeCapacity) {
	points.reserve(_size);
	points = _pBoard->getPoints(_ch, _size);
	setTopPoints();
}

void Ship::move(int difx, int dify) {
	deleteFromScreen();
	if (hasReachedEndPoint) return;

	for (int i = 0; i < points.size(); i++) {
		points[i].move(difx, dify);
	}
	drawOnScreen();
}

void Ship::drawOnScreen() const {
	Color::setTextColor(TextColor::CYAN);
	for (int i = 0; i < points.size(); i++) {
		points[i].drawOnScreen();
	}
	Color::setTextColor(TextColor::WHITE);
}

void Ship::deleteFromScreen() const {
	for (int i = 0; i < points.size(); i++) {
		points[i].deleteFromScreen();
	}
}

bool Ship::isShipIncludesPoint(Point p) const {
	for (int i = 0; i < points.size(); i++) {
		if (points[i].getX() == p.getX() && points[i].getY() == p.getY())
			return true;
	}

	return false;
}

bool Ship::isShipIncludesSomePoints(std::vector<Point> collisionPoints) const {
	for (int i = 0; i < collisionPoints.size(); i++) {
		if (isShipIncludesPoint(collisionPoints[i]))
			return true;
	}

	return false;
}

void Ship::setTopPoints() {
	char ch = points[0].getCh();
	int index = 0;

	for (int i = 0; i < points.size(); i++) {
		// Serching all ths points representing the top layer of the ship
		if (pBoard->get(points[i].getX(), points[i].getY() - 1) != ch) {
			topPointsIndexes[index] = i;
			index++;
		}
	}
}

std::vector<Point> Ship::getAboveShipPoints() const {
	std::vector<Point> abovePoints;

	// Iterating the indexes of the top point and insert them to "points"
	for (int i = 0; i < 2; i++) {
		int new_y = points[topPointsIndexes[i]].getY() - 1;
		int x = points[topPointsIndexes[i]].getX();
		Point newPoint(x, new_y, pBoard->get(x, new_y), pBoard);
		abovePoints.insert(abovePoints.end(), newPoint);
	}
	return abovePoints;
}

