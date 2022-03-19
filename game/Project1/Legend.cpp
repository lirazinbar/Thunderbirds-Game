#include "Legend.h"
#include"Ship.h"
#include "Timer.h"
#include "Board.h"

class Board;

Legend::Legend(Board* _pBoard): pBoard(_pBoard) {
	bool found = false;

	for (size_t row = 0; row < pBoard->Height && !found; ++row) {
		for (size_t col = 0; col < pBoard->Width && !found; col++) {
			if (pBoard->get(col, row) == '&') {  // Find the legend place on board
				legendLocation.setX(col);
				legendLocation.setY(row);
				found = true;
			}
		}
	}
}

void Legend::print(int activeShip, int timeLeft, int livesCount) const {
	gotoxy(legendLocation.getX(), legendLocation.getY());
	std::cout << "Active Ship: ";
	printActiveShip(activeShip);
	std::cout << "       Time Left: ";
	printTimer(timeLeft);
	std::cout << "       Lives: ";
	printLives(livesCount);
}

void Legend::printActiveShip(int activeShip) const {
	gotoxy(legendLocation.getX() + int(LegendElementsXLocation::ACTIVE_SHIP), legendLocation.getY());
	if (activeShip == int(ShipsIndex::BIG_SHIP)) {
		std::cout << "Big  ";
	}
	else {
		std::cout << "Small";
	}
}

void Legend::printLives(int livesCount) const {
	gotoxy(legendLocation.getX() + int(LegendElementsXLocation::LIVES), legendLocation.getY());
	std::cout << livesCount;
}

void Legend::printTimer(int timeLeft) const {
	// x coordination of the timer
	int x = getLegendLocation().getX() + int(LegendElementsXLocation::TIMER);
	// y coordination of the timer
	int y = getLegendLocation().getY();
	gotoxy(x, y);
	std::cout << timeLeft;
	if (timeLeft == 99) {
		gotoxy(x + 2, y);
		std::cout << ' ';  // Erase last digit
	}
	else if (timeLeft == 9) {
		gotoxy(x + 1, y);
		std::cout << ' ';  // Erase last digit
	}
}