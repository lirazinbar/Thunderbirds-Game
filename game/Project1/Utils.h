#pragma once

enum class BoardSymbols { END_POINT = 'E', LEGEND = '&', BIG_SHIP = '#', SMALL_SHIP = '@', BLANK = ' ', WALL = 'W' };

enum class PrintPoints { MESSAGE_X = 40, MESSAGE_Y = 10, ACTIVE_SHIP_X = 13, TIMER_X = 36, LIVES_X = 53 };

struct Keys {
	constexpr static char ESC = 27;
	constexpr static char Up = 'w';
	constexpr static char Right = 'd';
	constexpr static char Down = 'x';
	constexpr static char Left = 'a';
	constexpr static char BigShip = 'b';
	constexpr static char SmallShip = 's';
};

void gotoxy(int, int);
void clrscr();
void hide_cursor();
void printMainMenu(char& userChoice);
void printWinMessage();
void printLoseMessage(const char* deathReason = " ");
