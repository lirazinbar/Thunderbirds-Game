#include <iostream>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "utils.h"

// function definition -- requires windows.h
void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// function definition -- requires process.h
void clrscr()
{
	system("cls");
}

void hide_cursor()
{
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

int printMainMenu() {
	bool isValid = false;
	int num;

	clrscr();
	std::cout << "Hello and welcome to Thunderbirds! Please Choose an option: " << std::endl;
	std::cout << "(1) Start a new game" << std::endl;
	std::cout << "(8) Present instructions and keys" << std::endl;
	std::cout << "(9) EXIT" << std::endl;
	while (!isValid) {
		std::cin >> num;
		isValid = (num == 1 || num == 8 || num == 9);
	}

	return num;
}

void printWinMessage() {
	clrscr();
	std::cout << "Good job! you Win!" << std::endl;
}

void printLoseMessage() {
	clrscr();
	std::cout << "Game Over! you lose!" << std::endl;
}

char printPauseMessage() {
	bool isValid = false;
	char key = ' ';

	clrscr();
	std::cout << "Game paused, press ESC again to continue or 9 to Exit" << std::endl;
	while (!isValid) {
		if (_kbhit()) {
			key = _getch();
			isValid = (key == '9' || key == Keys::ESC);
		}
	}

	return key;
}
