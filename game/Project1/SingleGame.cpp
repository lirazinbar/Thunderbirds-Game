#include <conio.h>
#include <cctype>
#include <windows.h>
#include "SingleGame.h"
#include "Utils.h"
#include "Timer.h"

SingleGame::~SingleGame() {
	clrscr();
	if (gameWon == true) {
		Game::stopPlaying();
	}
	else {
		Game::decreseLives();
	}
}

void SingleGame::play() {
	char key = 0;

	while (keepPlaying == true) {
		if (_kbhit()) {
			key = _getch();
			assignKey(key);
		}
		moveShip();
		moveBlocksVertically();
		Sleep(400);
		timer.tick();
		if (isTimeRanOut() || isGameWon()) {
			keepPlaying = false;
		}
	}
}

void SingleGame::assignKey(char& key) {
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

bool SingleGame::isTimeRanOut() {
	// If the time past is grater than 1 sec
	if (timer.getDeltaTime() >= 1000) {
		timer.reduceTimeLeft();
		board.getLegend().printTimer(timer.getTimeLeft());
		timer.resetTickStartTime();
		// if time runs out
		if (timer.getTimeLeft() < 0) {
			if (livesCount != 1) {
				printLoseMessage("Time is up!");
			}
			return true;
		}
	}
	return false;
};

void SingleGame::pauseGame() {
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
			board.print(activeShip, timer.getTimeLeft(), livesCount);
		}
	}
}

void SingleGame::changeActiveShip(ShipsIndex _activeShip) {
	if (ships[int(_activeShip)].endPointStatus() == false) {
		activeShip = int(_activeShip);
		board.getLegend().printActiveShip(activeShip);
	}
}

bool SingleGame::isGameWon() {
	// If both ships have reached end point
	if (ships[int(ShipsIndex::BIG_SHIP)].endPointStatus() == true &&
		ships[int(ShipsIndex::SMALL_SHIP)].endPointStatus() == true) {
		gameWon = true;
		printWinMessage();
	}
	return gameWon;
}

void SingleGame::moveShip() {
	// If there is no change in direction
	if (dirx == 0 && diry == 0) return;
	// Get the points that will collide with another object
	std::vector<Point> points = board.checkMoving(ships[activeShip].getPoints(), ships[activeShip].getSize(), ships[activeShip].getChar(), dirx, diry);
	// If the ships doesn't collide with anything
	if (points.size() == 0) {
		checkBlocksAdjacentShip(ships[activeShip].getAboveShipPoints());
		ships[activeShip].move(dirx, diry);
		return;
	}
	// Check collision with wall & ships
	char collisionChars[2] = { (char)BoardSymbols::WALL, ships[(activeShip + 1) % 2].getChar() };
	if (areCharsInVec(points, collisionChars, 2)) {
		dirx = diry = 0;
		return;
	}
	// Check collision with block(s)
	if (checkShipPushBlock(points)) return;
	// check reaching the end point
	char exit[1] = { (char)BoardSymbols::END_POINT };
	if (areCharsInVec(points, exit, 1)) {
		ships[activeShip].setHasReachedEndPoint(true);
		ships[activeShip].move(dirx, diry);
		dirx = diry = 0;
		return;
	}
}

bool SingleGame::checkShipPushBlock(std::vector<Point> points) {
	// Checks if there are blocks the ship can move
	if (checkBlocksAdjacentShip(points)) {
		// Checks if there are blocks on top the ship, and if they can move
		checkBlocksAdjacentShip(ships[activeShip].getAboveShipPoints());
		ships[activeShip].move(dirx, diry);
		return true;
	}
	dirx = diry = 0;
	return false;
}

bool SingleGame::checkBlocksAdjacentShip(std::vector<Point> adjacentShipPoints) {
	int pointsIndex, blocksIndex;
	bool found = false;

	for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++, found = false) {
		for (pointsIndex = 0; pointsIndex < adjacentShipPoints.size() && !found; pointsIndex++) {
			if (blocks[blocksIndex].isBlockIncludesPoint(adjacentShipPoints[pointsIndex]) &&
				blocks[blocksIndex].getSize() <= ships[activeShip].getBlockSizeCapacity()) {
				found = true;
				if (isBlockCanMove(blocksIndex)) {
					blocks[blocksIndex].move(dirx, diry);
					return true;
				}
			}
		}
	}
	return false;
}

bool SingleGame::isBlockCanMove(int blockIndex) {
	return (board.checkMoving(blocks[blockIndex].getPoints(),
		blocks[blockIndex].getSize(), blocks[blockIndex].getChar(), dirx, diry).size() == 0);
}

void SingleGame::moveBlocksVertically() {
	std::vector<Point> points;
	int i;
	for (i = 0; i < blocksAmount; i++) {
		points = board.checkMoving(blocks[i].getPoints(), blocks[i].getSize(), blocks[i].getChar(), 0, 1);
		if (points.size() == 0) {
			blocks[i].move(0, 1);
		}
		else {
			checkBlockFallsOnShip(points, blocks[i].getSize());
		}
	}
}

void SingleGame::checkBlockFallsOnShip(std::vector<Point> points, int blockSize) {
	int shipIndex, pointIndex;
	for (pointIndex = 0; pointIndex < points.size(); pointIndex++) {
		for (shipIndex = 0; shipIndex < 2; shipIndex++) {
			if (ships[shipIndex].isShipIncludesPoint(points[pointIndex]) &&
				blockSize > ships[shipIndex].getBlockSizeCapacity()) {
				keepPlaying = false;
				printLoseMessage("Your ship has been smashed by a block!");
				return;
			}
		}
	}
}

bool SingleGame::areCharsInVec(std::vector<Point> points, char* charsArr, int size) {
	int i;
	for (i = 0; i < points.size(); i++) {
		if (isArrayIncludesChar(charsArr, size, points[i].getCh())) return true;
	}
	return false;
}

bool SingleGame::isArrayIncludesChar(char* arr, int size, char ch) {
	int i;
	for (i = 0; i < size; i++) {
		if (arr[i] == ch) return true;
	}
	return false;
}