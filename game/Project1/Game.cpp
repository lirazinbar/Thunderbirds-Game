#include <conio.h>
#include <cctype>
#include <windows.h>
#include "Game.h"

void Game::run() {
	char key = 0;
	bool keepRunning = true;
	board.print();
	while (keepRunning == true) {
		if (_kbhit()) {
			key = _getch();
			assignKey(key, keepRunning);
		}
		ships[activeShip].move(dirx, diry);
		Sleep(500);
	}
}

void Game::assignKey(char key, bool& keepRuning) {
	switch (std::tolower(key)) {
	case Keys::ESC:
		keepRuning = false;
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
