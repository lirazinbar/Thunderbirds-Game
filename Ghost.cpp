#include "Ghost.h"
#include "Color.h"

void Ghost::move(int dirx, int diry) {
	deleteFromScreen();
	point.move(dirx, diry);
	drawOnScreen();
}

void Ghost::drawOnScreen() const {
	Color::setTextColor(TextColor::LIGHTRED);
	point.drawOnScreen();
	Color::setTextColor(TextColor::WHITE);
}

void Ghost::deleteFromScreen() const {
	point.deleteFromScreen();
}