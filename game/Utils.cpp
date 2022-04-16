#include <iostream>
#include <ios>
#include <limits>
#include <conio.h>
#include <windows.h>
#include <process.h>
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

bool presentInstructions() {
	int key = 0;
	char ch = ' ';
	bool returnedValue, isValid = false;

	std::cout << "KEY:     |       EXPLANATION: " << std::endl;
	std::cout << "A        |			LEFT " << std::endl;
	std::cout << "D        |			RIGHT" << std::endl;
	std::cout << "W        |			UP" << std::endl;
	std::cout << "X        |			DOWN" << std::endl;
	std::cout << "B        |			Switch To The Big Ship" << std::endl;
	std::cout << "S        |			Switch To The Small Ship" << std::endl;

	std::cout << "Do You Want To Use The Colorful Version? " << std::endl;
	std::cout << "Y - Yes" << std::endl;
	std::cout << "N - NO" << std::endl;

	while (!isValid) {
		if (_kbhit()) {
			ch = _getch();
			isValid = (ch == 'Y' || ch == 'y' || ch == 'N' || ch == 'n');
		}
	}

	if (ch == 'Y' || ch == 'y') returnedValue = true;
	else returnedValue = false;

	std::cout << "Press 9 to return the menu" << std::endl;

	while (ch != '9') {
		if (_kbhit()) {
			ch = _getch();
		}
	}

	return returnedValue;
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

void printExitMessage() {
	clrscr();
	gotoxy(40, 10);
	std::cout << "Goodbye, thank you for playing!" << std::endl;
	gotoxy(40, 12);
	system("pause");
}

bool isExistInSet(std::set<int> setToCheck, int num) {
	std::set<int>::iterator itr;

	for (itr = setToCheck.begin(); itr != setToCheck.end(); itr++) {
		if (*itr == num) return true;
	}

	return false;
}

std::set<int> getIndexesInBothSets(std::set<int> set1, std::set<int> set2) {
	std::set<int> commonSet;
	std::set<int>::iterator itr;

	for (itr = set1.begin(); itr != set1.end(); itr++) {
		if (isExistInSet(set2, *itr)) {
			commonSet.insert(*itr);
		}
	}

	return commonSet;
}

std::set<int> reduceSets(std::set<int> set1, std::set<int> set2) {
	std::set<int> newSet;
	std::set<int>::iterator itr;

	for (itr = set1.begin(); itr != set1.end(); itr++) {
		if (!isExistInSet(set2, *itr)) {
			newSet.insert(*itr);
		}
	}

	return newSet;
}

bool isArrayIncludesChar(char* arr, int size, char ch) {
	int i;
	for (i = 0; i < size; i++) {
		if (arr[i] == ch) return true;
	}
	return false;
}