#include "Board.h"
#include "Point.h"
#include "Ship.h"
#include "HorizontalGhost.h"
#include "Color.h"

Board::Board() {
	resetCurrentBoard();
	legend.legendLocation = findCharOnBoard(char(BoardSymbols::LEGEND));
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

std::vector<HorizontalGhost> Board::loadHorizontalGhosts() {
	std::vector<HorizontalGhost> ghosts;

	for (int row = 0; row < Height; ++row) {
		char curr;
		for (int col = 0; (curr = get(col, row)) != '\n'; ++col) {
			if (curr == char(BoardSymbols::HORIZONTAL_GHOST)) {
				Point p = Point(col, row, char(BoardSymbols::HORIZONTAL_GHOST), this);
				HorizontalGhost ghost = HorizontalGhost(p, 1);

				ghosts.push_back(ghost);
			}
		}
	}

	return ghosts;
}

std::vector<Block> Board::loadBlocksRec() {
	std::vector<Point> points;
	std::vector<Block> blocks;
	std::vector<Point> checkedPoints;

	for (int row = 0; row < Height; ++row) {
		char curr;
		for (int col = 0; (curr = get(col, row)) != '\n'; ++col) {
			if (isCharOfBlock(curr)) {
				checkedPoints.clear();
				points = loadBlockWithChar(curr, col, row, blocks, checkedPoints);

				if (points.size() > 0) {
					Block block = Block(curr, points.size(), this, points);
					blocks.push_back(block);
				}
			}
		}
	}
	return blocks;
}

bool Board::isCharOfBlock(char ch) {
	return (ch != (char)BoardSymbols::SMALL_SHIP && ch != (char)BoardSymbols::BIG_SHIP 
		&& ch!= (char)BoardSymbols::WALL && ch != (char)BoardSymbols::BLANK
		&& ch != (char)BoardSymbols::END_POINT && ch != (char)BoardSymbols::LEGEND
		&& ch != (char)BoardSymbols::HORIZONTAL_GHOST);
}

std::vector<Point> Board::loadBlockWithChar(char ch, int col, int row, std::vector<Block> blocks, std::vector<Point> &checkedPoints) {
	std::vector<Point> points, temp;
	char curr = get(col, row);

	Point p = Point(col, row, ch, this);
	checkedPoints.push_back(p);
	if (curr == ch && !blocksIncludePoint(blocks, p)) {
		points.push_back(p);

		if (!arePointsIncludePoint(checkedPoints, col + 1, row)) {
			temp = loadBlockWithChar(ch, col + 1, row, blocks, checkedPoints);
			points.insert(points.end(), temp.begin(), temp.end());
		}

		if (!arePointsIncludePoint(checkedPoints, col - 1, row)) {
			temp = loadBlockWithChar(ch, col - 1, row, blocks, checkedPoints);
			points.insert(points.end(), temp.begin(), temp.end());
		}

		if (!arePointsIncludePoint(checkedPoints, col, row + 1)) {
			temp = loadBlockWithChar(ch, col, row + 1, blocks, checkedPoints);
			points.insert(points.end(), temp.begin(), temp.end());
		}

		if (!arePointsIncludePoint(checkedPoints, col, row - 1)) {
			temp = loadBlockWithChar(ch, col, row - 1, blocks, checkedPoints);
			points.insert(points.end(), temp.begin(), temp.end());
		}
	}
		
	return points;
}

bool Board::arePointsIncludePoint(std::vector<Point> points, int x, int y) const {
	for (int i = 0; i < points.size(); i++) {
		if (points[i].getX() == x && points[i].getY() == y)
			return true;
	}

	return false;
}

bool Board::blocksIncludePoint(std::vector<Block> blocks, Point p) {
	int i;

	for (i = 0; i < blocks.size(); i++) {
		if (blocks[i].isBlockIncludesPoint(p)) return true;
	}

	return false;
}

void Board::print(int activeShip, int timeLeft, int livesCount) const {
	for (size_t row = 0; row < Height; ++row) {
		std::cout << currentBoard[row];
	}
	legend.print(activeShip, timeLeft, livesCount);
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

std::vector<Point> Board::checkMoving(std::vector<Point> points, int size, char ch, int dirx, int diry) {
	std::vector<Point> collisionPoints;
	for (int i = 0; i < size; i++) {
		int new_x = points[i].getX() + dirx;
		int new_y = points[i].getY() + diry;
		Point newPoint(new_x, new_y, currentBoard[new_y][new_x], this);
		// TODO send the points of the block / ship and check if the point exiat in the vector indtead of currentBoard[new_y][new_x] != ch
		//if (currentBoard[new_y][new_x] != ' ' && currentBoard[new_y][new_x] != ch) { // pos is already taken
		if (currentBoard[new_y][new_x] != ' ' && !arePointsIncludePoint(points, new_x, new_y)) { // pos is already taken
			collisionPoints.push_back(newPoint);
		}
	}
	return collisionPoints;
}

void Board::Legend::print(int activeShip, int timeLeft, int livesCount) const {
	gotoxy(legendLocation.getX(), legendLocation.getY());
	Color::setTextColor(TextColor::GREEN);
	std::cout << "Active Ship: ";
	printActiveShip(activeShip);
	Color::setTextColor(TextColor::YELLOW);
	std::cout << "       Time Left: ";
	printTimer(timeLeft);
	Color::setTextColor(TextColor::LIGHTRED);
	std::cout << "       Lives: ";
	printLives(livesCount);
	Color::setTextColor(TextColor::WHITE);
}

void Board::Legend::printActiveShip(int activeShip) const {
	Color::setTextColor(TextColor::GREEN);
	gotoxy(legendLocation.getX() + int(PrintPoints::ACTIVE_SHIP_X), legendLocation.getY());
	if (activeShip == int(ShipsIndex::BIG_SHIP)) {
		std::cout << "Big  ";
	}
	else {
		std::cout << "Small";
	}
	Color::setTextColor(TextColor::WHITE);
}

void Board::Legend::printLives(int livesCount) const {
	gotoxy(legendLocation.getX() + int(PrintPoints::LIVES_X), legendLocation.getY());
	std::cout << livesCount;
}

void Board::Legend::printTimer(int timeLeft) const {
	Color::setTextColor(TextColor::YELLOW);
	// x coordination of the timer
	int x = getLegendLocation().getX() + int(PrintPoints::TIMER_X);
	// y coordination of the timer
	int y = getLegendLocation().getY();
	gotoxy(x, y);
	std::cout << timeLeft;
	if (timeLeft == 99) {
		gotoxy(x + 2, y);
		std::cout << char(BoardSymbols::BLANK);  // Erase last digit
	}
	else if (timeLeft == 9) {
		gotoxy(x + 1, y);
		std::cout << char(BoardSymbols::BLANK);  // Erase last digit
	}
	Color::setTextColor(TextColor::WHITE);
}