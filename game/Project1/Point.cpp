#include "Point.h"
#include "Board.h"

Point::Point(char ch, Board* _pBoard) : ch(ch), pBoard(_pBoard) { // Maybe getObjectLocation() in Board?
	for (int row = 0; row < pBoard->Height && !*this; ++row) {
		char curr;
		for (int col = 0; (curr = pBoard->get(col, row)) != '\n' && !*this; ++col) {
			if (curr == ch) {
				x = col;
				y = row;
			}
		}
	}
}

void Point::move(int& difx, int& dify) {
	int new_x = x + difx;
	int new_y = y + dify;
	if (pBoard->get(new_x, new_y) != ' ') { // pos is already taken
		difx = dify = 0;
		return;
	}
	deleteFromScreen();
	pBoard->set(x, y, ' '); // del also from board
	// TODO make sure not to get out of screen
	x = new_x;
	y = new_y;
	drawOnScreen();
	pBoard->set(x, y, ch); // draw also in board!
}
