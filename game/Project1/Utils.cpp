#include <iostream>
#include <windows.h>
#include <process.h>
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

	while (!isValid) {
		std::cout << "Hello and welcome to Thunderbirds! Please Choose an option: " << std::endl;
		std::cout << "(1) Start a new game" << std::endl;
		std::cout << "(8) Present instructions and keys" << std::endl;
		std::cout << "(9) EXIT" << std::endl;
		std::cin >> num;
		isValid = (num == 1 || num == 8 || num == 9);
	}

	return num;
}
