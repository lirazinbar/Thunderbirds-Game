#pragma once
#include <set>
#include <iterator>

enum class BoardSymbols {
	END_POINT = 'E',
	LEGEND = '&',
	BIG_SHIP = '#',
	SMALL_SHIP = '@',
	BLANK = ' ',
	WALL = 'W',
	HORIZONTAL_GHOST = '$',
	VERTICAL_GHOST = '!',
	WANDERING_GHOST = '%',
};

enum class PrintPoints {
	MESSAGE_X = 40,
	MESSAGE_Y = 10,
	ACTIVE_SHIP_X = 13,
	TIMER_X = 34, LIVES_X = 50,
	SCREEN_X = 65
};

struct Keys {
	constexpr static char ESC = 27;
	constexpr static char Up = 'w';
	constexpr static char Right = 'd';
	constexpr static char Down = 'x';
	constexpr static char Left = 'a';
	constexpr static char BigShip = 'b';
	constexpr static char SmallShip = 's';
	constexpr static char StartNewGame = '1';
	constexpr static char PlayFirstScreen = '1';
	constexpr static char PlaySpecificScreen = '2';
	constexpr static char Instructions = '8';
	constexpr static char Exit = '9';
	constexpr static char Yes = 'y';
	constexpr static char No = 'n';
};

// get x and y and set the cursor at this point on the screen
void gotoxy(int x, int y);
// Clearing the screen
void clrscr();
// Hiding the cursor from the screen
void hide_cursor();
// Printing the main menu
void printMainMenu(char& userChoice);
// Print the screen menu. The screen of the game will be set in this function
void printScreenMenu(std::ifstream& screenFile);
// Check if the file opened successfully
void checkFileOpening(std::ifstream& screenFile, char playerChoice);
// Presnting the game instrucions and asks the user if he wants to play in color
bool presentInstructions();
// Printing winning message
void printWinMessage();
// Printing losing message
void printLoseMessage(const char* deathReason);
// Printing an exit message
void printExitMessage();
// return true if the parameter exists in set
bool isExistInSet(std::set<int> setToCheck, int num);
// get the common indexes that exist in both sets
std::set<int> getIndexesInBothSets(std::set<int> set1, std::set<int> set2);
// get set1 minus set2
std::set<int> reduceSets(std::set<int> set1, std::set<int> set2);
// Checks if arr has ch in it  
bool isArrayIncludesChar(char* arr, int size, char ch);
