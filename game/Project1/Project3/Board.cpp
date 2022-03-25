#include "Board.h"
#include "Point.h"

Board::Board() {
	resetCurrentBoard();
}

std::vector<Point> Board::getPoints(char _ch, int _size) {
	std::vector<Point> points;
	for (int row = 0; row < Height && points.size() < _size; ++row) {
		char curr;
		for (int col = 0; (curr = get(col, row)) != '\n' && points.size() < _size; ++col) {
			if (curr == _ch) {
				Point p = Point(col, row, _ch, this);
				points.push_back(p);
			}
		}
	}
	return points;
}

void Board::print() const {
	for (size_t row = 0; row < Height; ++row) {
		std::cout << currentBoard[row];
	}
}
void Board::resetCurrentBoard() {
	for (size_t row = 0; row < Height; ++row) {
		strcpy_s(currentBoard[row], initialBoard[row]);
	}
}

Point Board::findCharOnBoard(char ch) {
	bool found = false;
	size_t row, col;
	Point res;

	for (row = 0; row < Height && !found; ++row) {
		for (col = 0; col < Width && !found; col++) {
			if (get(col, row) == ch) {
				res = Point(col, row, ch, this);
				found = true;
			}
		}
	}
	return res;
}

std::vector<Point> Board::checkMooving(std::vector<Point> points, int size, char ch, int dirx, int diry) {
	std::vector<Point> collisionPoints;
	for (int i = 0; i < size; i++) {
		int new_x = points[i].getX() + dirx;
		int new_y = points[i].getY() + diry;
		Point newPoint(new_x, new_y, currentBoard[new_y][new_x], this);
		if (currentBoard[new_y][new_x] != ' ' && currentBoard[new_y][new_x] != ch) { // pos is already taken
			collisionPoints.push_back(newPoint);
			// TODO: return all the chars collide with, if it's a wall we will put it first
			// return false;
		}
	}

	return collisionPoints;
	//return true;
}