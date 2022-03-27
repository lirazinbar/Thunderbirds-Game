#include <iostream>
#include <ios>
#include <limits>
#include <windows.h>
#include <process.h>
#include <conio.h>
#include "utils.h"
#include "Game.h"

// function definition -- requires windows.h
void gotoxy(int x, int y) {
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}

// function definition -- requires process.h
void clrscr() {
	system("cls");
}

void hide_cursor() {
	HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO info;
	info.dwSize = 100;
	info.bVisible = FALSE;
	SetConsoleCursorInfo(consoleHandle, &info);
}

void printMainMenu(char& userChoice) {
	bool isValid = false;

	clrscr();
	userChoice = 0;
	std::cout << "Hello and welcome to Thunderbirds! Please Choose an option: " << std::endl;
	std::cout << "(1) Start a new game" << std::endl;
	std::cout << "(8) Present instructions and keys" << std::endl;
	std::cout << "(9) EXIT" << std::endl;
	while (!isValid) {
		if (_kbhit()) {
			userChoice = _getch();
			isValid = (userChoice == '1' || userChoice == '8' || userChoice == '9');
		}
	}
	clrscr();
}

void printWinMessage() {
	clrscr();
	gotoxy(int(PrintPoints::MESSAGE_X), int(PrintPoints::MESSAGE_Y));
	std::cout << "Good job! You Won!\n" << std::endl;
	gotoxy(int(PrintPoints::MESSAGE_X), int(PrintPoints::MESSAGE_Y) + 2);
	system("pause");
}

void printLoseMessage(const char* deathReason) {
	clrscr();
	gotoxy(int(PrintPoints::MESSAGE_X), int(PrintPoints::MESSAGE_Y));
	int currentLivesCount = Game::getLivesCount() - 1;
	if (currentLivesCount > 0) {
		std::cout << deathReason << " You got " << currentLivesCount << " more lives" << std::endl;
	}
	else {
		std::cout << deathReason;
		gotoxy(int(PrintPoints::MESSAGE_X), int(PrintPoints::MESSAGE_Y) + 1);
		std::cout << "Unfortunately, You don't have more lives...";
		gotoxy(int(PrintPoints::MESSAGE_X), int(PrintPoints::MESSAGE_Y) + 2);
		std::cout << "Game Over! You lost!";
	}
	gotoxy(int(PrintPoints::MESSAGE_X), int(PrintPoints::MESSAGE_Y) + 4);
	system("pause");
}