
#include "Color.h"

bool Color::isInColorMode = false;

void Color::setTextColor(const TextColor& colorToSet) {
	if (isInColorMode)
		SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), (int)colorToSet);
}