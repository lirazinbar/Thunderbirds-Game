#include <conio.h>
#include <cctype>
#include <windows.h>
#include "Game.h"
#include "Utils.h"

void Game::run() {
	char key = 0;
	bool keepRunning = true;
	board.print();
	while (keepRunning == true) {
		ships[activeShip].move(dirx, diry);
		block.move();
		Sleep(500);

		if (_kbhit()) {
			key = _getch();
			assignKey(key, keepRunning);
		}
	}
}

void Game::assignKey(char key, bool& keepRuning) {
	char userInput;
	switch (std::tolower(key)) {
	case Keys::ESC:
		userInput = printPauseMessage();
		if(userInput == '9') keepRuning = false;
		else {
			clrscr();
			board.print();
		}
		dirx = 0;
		diry = 0;
		break;
	case Keys::Up:
		dirx = 0;
		diry = -1;
		break;
	case Keys::Right:
		dirx = 1;
		diry = 0;
		break;
	case Keys::Down:
		dirx = 0;
		diry = 1;
		break;
	case Keys::Left:
		dirx = -1;
		diry = 0;
		break;
	case Keys::BigShip:
		activeShip = int(ShipsIndex::BIG_SHIP);
		dirx = 0;
		diry = 0;
		break;
	case Keys::SmallShip:
		activeShip = int(ShipsIndex::SMALL_SHIP);
		dirx = 0;
		diry = 0;
		break;
	}
}
