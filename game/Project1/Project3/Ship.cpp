#include "Ship.h"
#include "Point.h"
#include "Board.h"
#include "Utils.h"
#include "Color.h"

Ship::Ship(char _ch, int _size, Board* _pBoard, int _blockSizeCapacity) : ch(_ch), size(_size), pBoard(_pBoard), blockSizeCapacity(_blockSizeCapacity){
	points = _pBoard->getPoints(_ch, _size);
}

//std::vector<Point> Ship::checkMooving(int difx, int dify) const{
//	std::vector<Point> collisionPoints;
//	for (int i = 0; i < size; i++) {
//		int newX = points[i].getX() + difx;
//		int newY = points[i].getY() + dify;
//		Point newPoint = { newX, newY,  pBoard->get(newX, newY), pBoard };
//		//char newPoint = pBoard->get((points[i].getX() + difx), (points[i].getY() + dify));
//		if (newPoint.getCh() != char(BoardSymbols::BLANK) && newPoint.getCh() != ch) { // pos is already taken
//			//difx = dify = 0;
//			// If at least one of the points of the ship has reachd the end point
//			// Error - if 1 point of the ship is collide with wall...
//			//if (newPoint == char(BoardSymbols::END_POINT)) {
//			//	hasReachedEndPoint = true;
//			//}
//			collisionPoints.push_back(newPoint);
//		}
//	}
//
//	return collisionPoints;
//}

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

bool Ship::isShipIncludesPoint(Point p) {
	for (int i = 0; i < points.size(); i++) {
		if (points[i].getX() == p.getX() && points[i].getY() == p.getY())
			return true;
	}

	return false;
}
