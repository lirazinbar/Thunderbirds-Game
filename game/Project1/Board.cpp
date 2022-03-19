#include "Board.h"
#include "Point.h"

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