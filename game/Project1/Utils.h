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

// get x and y and set the cursor at this point on the screen
void gotoxy(int x, int y);
// Clearing the screen
void clrscr();
// Hiding the cursor from the screen
void hide_cursor();
// Printing the main menu
void printMainMenu(char& userChoice);
// Presnting the game instrucions and asks the user if he wants to play in color
bool presentInstructions();
// Printing winning message
void printWinMessage();
// Printing losing message
void printLoseMessage(const char* deathReason);
// Printing an exit message
void printExitMessage();
