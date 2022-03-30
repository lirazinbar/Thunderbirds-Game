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

	while (userChoice != '9') {
		printMainMenu(userChoice);
		if (userChoice == '1') {
			resetGame();
			while (keepPlaying == true) {
				moveShip();
				moveBlocksVertically();
				Sleep(500);
				timer.tick();
				if (checkTime() <= 0) { //If time runs out
					decreseLives();
				}
				checkGameWin();
				checkGameLose();
				if (_kbhit()) {
					key = _getch();
					assignKey(key);
				}
			}
		}
		else if (userChoice == '8') {
			//color.setColorMode(presentInstructions());
			Color::setColorMode(presentInstructions());
		}
	}

	printExitMessage();
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

void Game::resetGame() {
	livesCount = 3;
	resetScreen();
	keepPlaying = true;
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
	resetBlocks();
	board.print();
	legend.print(activeShip, timer.getTimeLeft(), livesCount);
}

void Game::resetShips() {
	ships[0].resetLocatin();
	ships[1].resetLocatin();
}

void Game::resetBlocks() {
	for (int i = 0; i < blocksAmount; i++) {
		blocks[i].resetLocatin();
	}
}

void Game::moveShip() {
	if (dirx == 0 && diry == 0) return;
	std::vector<Point> points = board.checkMooving(ships[activeShip].getPoints(), ships[activeShip].getSize(), ships[activeShip].getChar(), dirx, diry);
	if (points.size() == 0) {
		ships[activeShip].move(dirx, diry);
		return;
	}
	// check collisions wall & ships
	char staticChars[2] = { (char)BoardSymbols::WALL, ships[(activeShip + 1) % 2].getChar() };
	if (areCharsInVec(points, staticChars, 2)) {
		dirx = diry = 0;
		return;
	}

	if (checkShipPushBlock(points)) return;

	// check if can exit = all chars in vec are 'E', do it before checkShipPushBlock
	char exit[1] = { (char)BoardSymbols::END_POINT };

	if (areCharsInVec(points, exit, 1)) {
		ships[activeShip].setHasReachedEndPoint(true);
		ships[activeShip].move(dirx, diry);
		dirx = diry = 0;
	}
}

bool Game::checkShipPushBlock(std::vector<Point> points) {
	bool canMove, isColide;
	//std::vector<int> blocksIndexesToMove = getBlocksCanMoveAfterCollideByShip(points, canMove, isColide);
	std::set<int> blocksIndexesToMove = getBlocksCanMoveAfterCollideByShip(points, canMove, isColide);
	int totalSize = getTotalSizeOfBlocks(blocksIndexesToMove);

	if (!canMove || totalSize > ships[activeShip].getBlockSizeCapacity()) {
		dirx = diry = 0;
		return isColide;
	}

	if (isColide) {
		MoveBlocksAndShip(blocksIndexesToMove);
	}

	return isColide;


	/*
	for (pointsIndex = 0; pointsIndex < points.size(); pointsIndex++) {
		for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++) {
			if (blocks[blocksIndex].isBlockIncludesPoint(points[pointsIndex]) &&
				blocks[blocksIndex].getSize() <= ships[activeShip].getBlockSizeCapacity()) {
				if (isBlockCanMove(blocksIndex)) {
					blocks[blocksIndex].move(dirx, diry);
					ships[activeShip].move(dirx, diry);
				}
				else {
					dirx = diry = 0;
				}
				return true;
			}
		}
	}
	*/

	//return false;
}

//// TODO: fix to set structure
////std::vector<int> Game::getBlocksCanMoveAfterCollideByShip(std::vector<Point> points, bool& canMove, bool& isColide) {
//std::set<int> Game::getBlocksCanMoveAfterCollideByShip(std::vector<Point> points, bool& canMove, bool& isColide) {
//	int blocksIndex, pointsIndex, totalSize = 0;
//	//std::vector<int> blocksIndexesToMove;
//	std::set<int> blocksIndexesToMove;
//	isColide = false;
//
//	for (pointsIndex = 0; pointsIndex < points.size(); pointsIndex++) {
//		for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++) {
//			if (blocks[blocksIndex].isBlockIncludesPoint(points[pointsIndex])) { // ship is collide with the block
//				isColide = true;
//				if (totalSize + blocks[blocksIndex].getSize() <= ships[activeShip].getBlockSizeCapacity() && isBlockCanMove(blocksIndex)) {
//					//blocksIndexesToMove.push_back(blocksIndex);
//					blocksIndexesToMove.insert(blocksIndex);
//					totalSize += blocks[blocksIndex].getSize();
//				}
//				else {
//					canMove = false;
//					return blocksIndexesToMove;
//				}
//			}
//		}
//	}
//
//	canMove = true;
//	return blocksIndexesToMove;
//}

// TODO: also check Size
std::set<int> Game::getBlocksCanMoveAfterCollideByShip(std::vector<Point> points, bool& canMove, bool& isColide) {
	int blocksIndex, pointsIndex;
	//std::vector<int> blocksIndexesToMove;
	std::set<int> blocksIndexesToMove, nextBlocksIndexesToMove;
	std::vector<Point> allCollisionPoints;
	isColide = false;

	// if all points are not collide return null set - blocksIndexesToMove;
	if (isAllVecIncludesChar(points, ' ')) {
		isColide = true;
		canMove = true;
		return blocksIndexesToMove;
	}
	
	// if one of the points colides with wall return is colide-true, and canMove-false, or the other ship
	char staticChars[2] = { (char)BoardSymbols::WALL, ships[(activeShip + 1) % 2].getChar() };
	if (areCharsInVec(points, staticChars, 2)) {
		isColide = true;
		canMove = false;
		return blocksIndexesToMove;
	}

	// get the blocks that the points are collide with
	for (pointsIndex = 0; pointsIndex < points.size(); pointsIndex++) {
		for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++) {
			if (blocks[blocksIndex].isBlockIncludesPoint(points[pointsIndex])) { // the point is collide with the block
				isColide = true;
				blocksIndexesToMove.insert(blocksIndex);
				//if (totalSize + blocks[blocksIndex].getSize() <= ships[activeShip].getBlockSizeCapacity() && isBlockCanMove(blocksIndex)) {
				//	//blocksIndexesToMove.push_back(blocksIndex);
				//	blocksIndexesToMove.insert(blocksIndex);
				//	totalSize += blocks[blocksIndex].getSize();
				//}
				//else {
				//	canMove = false;
				//	return blocksIndexesToMove;
				//}
				
			}
		}
	}

	allCollisionPoints = getTheNextCollisionPointsOfBlocks(blocksIndexesToMove);
	nextBlocksIndexesToMove = getBlocksCanMoveAfterCollideByShip(allCollisionPoints, canMove, isColide);

	if (canMove) {
		std::set<int> newSet;
		std::set_union(blocksIndexesToMove.begin(), blocksIndexesToMove.end(), nextBlocksIndexesToMove.begin(), nextBlocksIndexesToMove.end(), std::inserter(newSet, newSet.begin()));
		return newSet;
	}

	std::set<int> emptySet;
	return emptySet;
}

int Game::getTotalSizeOfBlocks(std::set<int> blocksIndexesToMove) {
	std::set<int>::iterator itr;
	int totalSize = 0;

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		totalSize += blocks[*itr].getSize();
	}

	return totalSize;
}

std::vector<Point> Game::getTheNextCollisionPointsOfBlocks(std::set<int> blocksIndexesToMove) {
	std::vector<Point> points, tempPoints;
	std::set<int>::iterator itr;

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		tempPoints = board.checkMooving(blocks[*itr].getPoints(), blocks[*itr].getSize(), blocks[*itr].getChar(), dirx, diry);
		points.reserve(points.size() + tempPoints.size());
		points.insert(points.end(), tempPoints.begin(), tempPoints.end());
	}

	return points;
}


//void Game::MoveBlocksAndShip(std::vector<int> blocksIndexesToMove) {
void Game::MoveBlocksAndShip(std::set<int> blocksIndexesToMove) {
	std::set<int>::iterator itr;

	//for (int i = 0; i< blocksIndexesToMove.size(); i++) {
	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		//blocks[blocksIndexesToMove[i]].move(dirx, diry);
		//blocks[*itr].move(dirx, diry);
		blocks[*itr].deleteFromScreen();
	}

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		//blocks[blocksIndexesToMove[i]].move(dirx, diry);
		//blocks[*itr].move(dirx, diry);
		blocks[*itr].setPointsIndexes(dirx, diry);
		blocks[*itr].drawOnScreen();
	}
	
	ships[activeShip].move(dirx, diry);
}

bool Game::isBlockCanMove(int blockIndex) {
	return (board.checkMooving(blocks[blockIndex].getPoints(),
		blocks[blockIndex].getSize(), blocks[blockIndex].getChar(), dirx, diry).size() == 0);
}

// add check of falling on ship
void Game::moveBlocksVertically() {
	std::vector<Point> points;
	int i;
	for (i = 0; i < blocksAmount; i++) {
		points = board.checkMooving(blocks[i].getPoints(), blocks[i].getSize(), blocks[i].getChar(), 0, 1);
		if (points.size() == 0) {
			blocks[i].move(0, 1);
		}
		else {
			checkBlockFallsOnShip(points, blocks[i].getSize());
		}
	}
}

void Game::checkBlockFallsOnShip(std::vector<Point> points, int blockSize) {
	int shipIndex, pointIndex;
	for (pointIndex = 0; pointIndex < points.size(); pointIndex++) {
		for (shipIndex = 0; shipIndex < 2; shipIndex++) {
			if (ships[shipIndex].isShipIncludesPoint(points[pointIndex]) &&
				blockSize > ships[shipIndex].getBlockSizeCapacity()) {
				decreseLives();
				return;
			}
		}
	}
}

bool Game::areCharsInVec(std::vector<Point> points, char* charsArr, int size) {
	int i;
	for (i = 0; i < points.size(); i++) {
		if (isArrayIncludesChar(charsArr, size, points[i].getCh())) return true;
	}

	return false;
}

bool Game::isArrayIncludesChar(char* arr, int size, char ch) {
	int i;
	for (i = 0; i < size; i++) {
		if (arr[i] == ch) return true;
	}

	return false;
}

bool Game::isAllVecIncludesChar(std::vector<Point> points, char ch) {
	int i;
	for (i = 0; i < points.size(); i++) {
		if (points[i].getCh() != ch) return false;
	}

	return true;
}