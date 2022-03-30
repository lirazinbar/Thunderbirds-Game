#include "Legend.h"
#include"Ship.h"
#include "Timer.h"
#include "Board.h"
#include "Color.h"

class Board;

Legend::Legend(Board* _pBoard) : pBoard(_pBoard) {
	legendLocation = pBoard->findCharOnBoard(char(BoardSymbols::LEGEND));
}

void Legend::print(int activeShip, int timeLeft, int livesCount) const {
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

void Legend::printActiveShip(int activeShip) const {
	Color::setTextColor(TextColor::GREEN);
	gotoxy(legendLocation.getX() + int(LegendElementsXLocation::ACTIVE_SHIP), legendLocation.getY());
	if (activeShip == int(ShipsIndex::BIG_SHIP)) {
		std::cout << "Big  ";
	}
	else {
		std::cout << "Small";
	}
	Color::setTextColor(TextColor::WHITE);
}

void Legend::printLives(int livesCount) const {
	gotoxy(legendLocation.getX() + int(LegendElementsXLocation::LIVES), legendLocation.getY());
	std::cout << livesCount;
}

void Legend::printTimer(int timeLeft) const {
	Color::setTextColor(TextColor::YELLOW);
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
	Color::setTextColor(TextColor::WHITE);
}