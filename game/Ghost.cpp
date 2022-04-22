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

int Ghost::isGhostExistInPointsVec(std::vector<Point> points) {
	for (int i = 0; i < points.size(); i++) {
		if (point == points[i]) {
			return i;
		}
	}

	return -1;
}