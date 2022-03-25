#include <conio.h>
#include <cctype>
#include <windows.h>
#include "Game.h"
#include "Utils.h"
#include "Timer.h"
#include "Legend.h"


void Game::run() {
	char key = 0;
	char userChoice = 0;

	while (userChoice != Keys::ESC) {
		printMainMenu(userChoice);
		if (userChoice == '1') {
			resetScreen();
			keepPlaying = true;
			while (keepPlaying == true) {
				moveShip();
				moveBlockVertically();
				Sleep(100);
				timer.tick();
				if (checkTime() <= 0) { //If time runs out
					decreseLives();
					if (!checkGameLose()) {
						resetScreen();
					}
				}
				if (_kbhit()) {
					key = _getch();
					assignKey(key);
				}
				checkGameWin();
			}
		}
		else if (userChoice == '8') {
			//color.setColorMode(presentInstructions());
			Color::setColorMode(presentInstructions());
		}
	}
}

void Game::assignKey(char& key) {
	switch (std::tolower(key)) {
	case Keys::ESC:
		pauseGame();
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
		changeActiveShip(ShipsIndex::BIG_SHIP);
		dirx = 0;
		diry = 0;
		break;
	case Keys::SmallShip:
		changeActiveShip(ShipsIndex::SMALL_SHIP);
		dirx = 0;
		diry = 0;
		break;
	}
}

int Game::checkTime() {
	// If the time past is grater than 1 sec
	if (timer.getDeltaTime() >= 1000) {
		timer.reduceTimeLeft();
		legend.printTimer(timer.getTimeLeft());
		timer.resetTickStartTime();
	}
	return timer.getTimeLeft();
};

void Game::pauseGame() {
	char key = 0;

	clrscr();
	gotoxy(10, 10);
	std::cout << "Game paused, press ESC again to continue or 9 to Exit" << std::endl;
	while (key != '9' && key != Keys::ESC) {
		if (_kbhit()) {
			key = _getch();
		}
		if (key == '9') {
			keepPlaying = false;
			clrscr();
		}
		else if (key == Keys::ESC) {
			clrscr();
			board.print();
			legend.print(activeShip, timer.getTimeLeft(), livesCount);
		}
	}
}

void Game::changeActiveShip(ShipsIndex _activeShip) {
	if (ships[int(_activeShip)].endPointStatus() == false) {
		activeShip = int(_activeShip);
		legend.printActiveShip(activeShip);
	}
}

bool Game::checkGameLose() {
	bool isLost = false;

	if (livesCount == 0) {
		isLost = true;
		keepPlaying = false;
		printLoseMessage();
	}
	return isLost;
}

void Game::checkGameWin() {
	// If both ships has reaced the end point
	if (ships[int(ShipsIndex::BIG_SHIP)].endPointStatus() == true &&
		ships[int(ShipsIndex::SMALL_SHIP)].endPointStatus() == true) {
		keepPlaying = false;
		printWinMessage();
	}
}

void Game::resetScreen() {
	clrscr();
	dirx = diry = 0;
	board.resetCurrentBoard();
	timer.resetTimer();
	resetShips();
	//resetBlocks();
	board.print();
	legend.print(activeShip, timer.getTimeLeft(), livesCount);
}

void Game::resetShips() {
	ships[0].resetLocatin();
	ships[1].resetLocatin();
}

//void Game::resetBlocks() {
//	for (size_t i; i < blocks.size(); i++) {
//		blocks[i].resetLocation();
//	}
//}

void Game::moveShip() {
	if ((dirx != 0 || diry != 0) && board.checkMooving(ships[activeShip].getPoints(), ships[activeShip].getSize(), ships[activeShip].getChar(), dirx, diry).size() == 0) ships[activeShip].move(dirx, diry);
	else {
		dirx = diry = 0;
	}
}

void Game::moveBlockVertically() {
	if (board.checkMooving(block.getPoints(), block.getSize(), block.getChar(), 0, 1).size() == 0) block.move(0, 1);
}
