#include <conio.h>
#include <cctype>
#include <windows.h>
#include "SingleGame.h"
#include "Utils.h"
#include "Timer.h"

SingleGame::SingleGame(int _livesCount) : livesCount(_livesCount) {
	board.print(activeShip, timer.getTimeLeft(), livesCount); 
	blocks = board.loadBlocksRec(); 
	blocksAmount = blocks.size();
};

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

	while (keepPlayingSingleGame == true) {
		moveShip();
		moveBlocksVertically();
		Sleep(600);
		timer.tick();
		if (isTimeRanOut() || isGameWon()) {
			keepPlayingSingleGame = false;
		}
		if (_kbhit()) {
			key = _getch();
			assignKey(key);
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
			printLoseMessage("Time is up!");
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
			keepPlayingSingleGame = false;
			Game::stopPlaying();
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
		checkBlocksAboveShip(ships[activeShip].getAboveShipPoints());
		//ships[activeShip].move(dirx, diry);
		return;
	}
	// Check collision with wall & ships
	char collisionChars[2] = { (char)BoardSymbols::WALL, ships[(activeShip + 1) % 2].getChar() };
	if (arePointsHaveChars(points, collisionChars, 2)) {
		dirx = diry = 0;
		return;
	}
	// check reaching the end point
	if (areAllPointsIncludeChar(points, (char)BoardSymbols::END_POINT)) {
		ships[activeShip].setHasReachedEndPoint(true);
		ships[activeShip].move(dirx, diry);
		dirx = diry = 0;
		return;
	}
	// Check collision with block(s)
	if (checkShipPushBlock(points)) {
		// TODO check this in the rec above, with the checking of the blocks above blocks rec
		// checkBlocksAboveShip(ships[activeShip].getAboveShipPoints());
	}
}

bool SingleGame::checkShipPushBlock(std::vector<Point> points) {
	bool canMove, isColide;
	std::set<int> blocksAbove, blocksAboveToMove, blocksAboveBlocks, allBlocksToMove, blocksAboveShip;
	std::set<int> blocksIndexesToMove = getBlocksCanMoveAfterCollideByShip(points, canMove, isColide, blocksAboveBlocks);
	blocksAboveShip = getAllBlocksAboveBlock(ships[activeShip].getAboveShipPoints());
	std::set_union(blocksAboveShip.begin(), blocksAboveShip.end(), blocksAboveBlocks.begin(), blocksAboveBlocks.end(), std::inserter(blocksAbove, blocksAbove.begin()));
	blocksAboveToMove = getOnlyBlocksAboveToMove(blocksAbove, blocksIndexesToMove);
	// checkBlocksAboveShip(ships[activeShip].getAboveShipPoints());
	std::set_union(blocksAboveToMove.begin(), blocksAboveToMove.end(), blocksIndexesToMove.begin(), blocksIndexesToMove.end(), std::inserter(allBlocksToMove, allBlocksToMove.begin()));
	int totalSize = getTotalSizeOfBlocks(allBlocksToMove); // calc also the blocks above

	if (!canMove || totalSize > ships[activeShip].getBlockSizeCapacity()) {
		dirx = diry = 0;
		return isColide;
	}

	if (isColide) {
		MoveBlocksAndShip(blocksIndexesToMove);
		// move blocks above
		checkBlocksAboveAndMove(blocksAboveToMove);
	}
	return isColide;
}

std::set<int> SingleGame::getOnlyBlocksAboveToMove(std::set<int> blocksAbove, std::set<int> blocksIndexesToMove) {
	std::set<int> blocksAboveToMove;
	std::set<int>::iterator itr;

	for (itr = blocksAbove.begin(); itr != blocksAbove.end(); itr++) {
		if (!isExistInSet(blocksIndexesToMove, *itr)) blocksAboveToMove.insert(*itr);
	}

	return blocksAboveToMove;

}

bool SingleGame::isExistInSet(std::set<int> setToCheck, int num) {
	std::set<int>::iterator itr;

	for (itr = setToCheck.begin(); itr != setToCheck.end(); itr++) {
		if (*itr == num) return true;
	}

	return false;
}

std::set<int> SingleGame::getBlocksCanMoveAfterCollideByShip(std::vector<Point> points, bool& canMove, bool& isColide, std::set<int> &blocksAbove) {
	int blocksIndex, pointsIndex;
	std::set<int> blocksIndexesToMove, nextBlocksIndexesToMove, tempBlocks;
	std::vector<Point> allCollisionPoints, collisionPointsAbove;
	isColide = false;

	// if all points are not collide return null set - blocksIndexesToMove;
	if (areAllPointsIncludeChar(points, ' ')) {
		isColide = true;
		canMove = true;
		return blocksIndexesToMove;
	}

	// if one of the points colides with wall return is colide-true, and canMove-false, or the other ship
	char staticChars[2] = { (char)BoardSymbols::WALL, ships[(activeShip + 1) % 2].getChar() };
	if (arePointsHaveChars(points, staticChars, 2)) {
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
				// get blocks above recursively
				collisionPointsAbove = getTheNextCollisionPointsOfBlocks({ blocksIndex }, 0, -1);
				tempBlocks = getAllBlocksAboveBlock(collisionPointsAbove);
				std::set_union(blocksAbove.begin(), blocksAbove.end(), tempBlocks.begin(), tempBlocks.end(), std::inserter(blocksAbove, blocksAbove.begin()));
			}
		}
	}

	allCollisionPoints = getTheNextCollisionPointsOfBlocks(blocksIndexesToMove, dirx, diry);
	nextBlocksIndexesToMove = getBlocksCanMoveAfterCollideByShip(allCollisionPoints, canMove, isColide, blocksAbove);

	if (canMove) {
		std::set<int> newSet;
		std::set_union(blocksIndexesToMove.begin(), blocksIndexesToMove.end(), nextBlocksIndexesToMove.begin(), nextBlocksIndexesToMove.end(), std::inserter(newSet, newSet.begin()));
		return newSet;
	}

	std::set<int> emptySet;
	return emptySet;
}

std::set<int> SingleGame::getAllBlocksAboveBlock(std::vector<Point> points) {
	int blocksIndex, pointsIndex;
	std::set<int> blocksIndexesToMove, nextBlocksIndexesToMove;
	std::vector<Point> allCollisionPoints;

	// if all points are not collide return null set - blocksIndexesToMove;
	// char staticChars[2] = { (char)BoardSymbols::WALL, ships[(activeShip + 1) % 2].getChar() };
	if (points.size() == 0 || areAllPointsIncludeChar(points, (char)BoardSymbols::BLANK) || 
		areAllPointsIncludeChar(points, (char)BoardSymbols::END_POINT) || 
		areAllPointsIncludeChar(points, ships[(activeShip + 1) % 2].getChar())) {
		return blocksIndexesToMove;
	}

	// get the blocks that the points are collide with
	for (pointsIndex = 0; pointsIndex < points.size(); pointsIndex++) {
		for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++) {
			if (blocks[blocksIndex].isBlockIncludesPoint(points[pointsIndex])) { // the point is collide with the block
				blocksIndexesToMove.insert(blocksIndex);
				// get blocks above recursively :)
			}
		}
	}

	allCollisionPoints = getTheNextCollisionPointsOfBlocks(blocksIndexesToMove, 0, -1);
	nextBlocksIndexesToMove = getAllBlocksAboveBlock(allCollisionPoints);


	std::set<int> newSet;
	std::set_union(blocksIndexesToMove.begin(), blocksIndexesToMove.end(), nextBlocksIndexesToMove.begin(), nextBlocksIndexesToMove.end(), std::inserter(newSet, newSet.begin()));
	return newSet;
}


int SingleGame::getTotalSizeOfBlocks(std::set<int> blocksIndexesToMove) const {
	std::set<int>::iterator itr;
	int totalSize = 0;

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		totalSize += blocks[*itr].getSize();
	}

	return totalSize;
}

std::vector<Point> SingleGame::getTheNextCollisionPointsOfBlocks(std::set<int> blocksIndexesToMove, int _dirx, int _diry) {
	std::vector<Point> points, tempPoints;
	std::set<int>::iterator itr;

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		tempPoints = board.checkMoving(blocks[*itr].getPoints(), blocks[*itr].getSize(), blocks[*itr].getChar(), _dirx, _diry);
		points.reserve(points.size() + tempPoints.size());
		points.insert(points.end(), tempPoints.begin(), tempPoints.end());
	}

	return points;
}

void SingleGame::MoveBlocksAndShip(std::set<int> blocksIndexesToMove) {
	moveBlocks(blocksIndexesToMove);
	//ships[activeShip].move(dirx, diry);
}

// TODO have to be a recursive check
void SingleGame::checkBlocksAboveAndMove(std::set<int> blocksIndexesToMove) {
	bool canMove, isColide;
	std::set<int> blocksAbove, getblocksToMove, movedBlocks;
	std::set<int>::iterator itr;

	ships[activeShip].deleteFromScreen();

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end() && !isExistInSet(movedBlocks, *itr); itr++) {
		getblocksToMove = getBlocksCanMoveAfterCollideByShip(blocks[*itr].getPoints(), canMove, isColide, blocksAbove);
		if (canMove) {
			moveBlocks(getblocksToMove);
			std::set_union(getblocksToMove.begin(), getblocksToMove.end(), movedBlocks.begin(), movedBlocks.end(), std::inserter(movedBlocks, movedBlocks.begin()));
		}
	}

	ships[activeShip].setPointsIndexes(dirx, diry);
	ships[activeShip].drawOnScreen();
}

void SingleGame::moveBlocks(std::set<int> blocksIndexesToMove) {
	std::set<int>::iterator itr;

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		blocks[*itr].deleteFromScreen();
	}

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		blocks[*itr].setPointsIndexes(dirx, diry);
		blocks[*itr].drawOnScreen();
	}

}

bool SingleGame::isBlockCanMove(int blockIndex) {
	std::vector<Point> collisionPoints = board.checkMoving(blocks[blockIndex].getPoints(),
		blocks[blockIndex].getSize(), blocks[blockIndex].getChar(), dirx, diry);
	return (collisionPoints.size() == 0 || areAllPointsIncludeChar(collisionPoints, ships[activeShip].getChar()));
}

bool SingleGame::checkBlocksAboveShip(std::vector<Point> adjacentShipPoints) {
	// TODO change to void
	std::set<int> blocksAbove = getAllBlocksAboveBlock(adjacentShipPoints);
	std::set<int>::iterator itr;

	int blocksIndex;
	//bool found = false;

	//for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++, found = false) {
	//	for (pointsIndex = 0; pointsIndex < adjacentShipPoints.size() && !found; pointsIndex++) {
	//		if (blocks[blocksIndex].isBlockIncludesPoint(adjacentShipPoints[pointsIndex]) &&
	//			blocks[blocksIndex].getSize() <= ships[activeShip].getBlockSizeCapacity()) {
	//			found = true;
	//			if (isBlockCanMove(blocksIndex)) {
	//				blocks[blocksIndex].move(dirx, diry);
	//				return true;
	//			}
	//		}
	//	}
	//}

	// TODO total size of blocks is checked in other function
	if (blocksAbove.size() == 0) {
		ships[activeShip].move(dirx, diry);
		return false;
	}


	/*for (itr = blocksAbove.begin(); itr != blocksAbove.end(); itr++) {
		if (isBlockCanMove(*itr)) {
			blocks[*itr].move(dirx, diry);
		}
	}*/
	checkBlocksAboveAndMove(blocksAbove);
	return true;
}

void SingleGame::moveBlocksVertically() {
	std::vector<Point> points;
	int i, totalSizeOfBlocks;
	char staticChars[2] = { (char)BoardSymbols::END_POINT, (char)BoardSymbols::WALL };
	std::set<int> blocksIndexesAbove;


	for (i = 0; i < 2; i++) {
		getBlocksFallOnShipTopPoints(ships[i].getAboveShipPoints(), blocksIndexesAbove); // TODO check each ship & move all the blocks in 1 piece
		totalSizeOfBlocks = getTotalSizeOfBlocks(blocksIndexesAbove);

		if (ships[i].getBlockSizeCapacity() < totalSizeOfBlocks) { // TODO check if the other ship / the walls are not already hold the blocks
			keepPlayingSingleGame = false;
			printLoseMessage("Your ship has been smashed by a block! ");
			return;
		}
		blocksIndexesAbove.clear();
	}


	for (i = 0; i < blocksAmount; i++) {
		points = board.checkMoving(blocks[i].getPoints(), blocks[i].getSize(), blocks[i].getChar(), 0, 1);
		if (points.size() == 0) {
			blocks[i].move(0, 1);
		}
		// TODO - else - check recursive + checking of ship smash
		// Return true if the ship has been smashed by a block
		/*else if (!arePointsHaveChars(points, staticChars, 2) && checkBlockFallsOnShip(points, blocks[i].getSize())) {
			break;
		}*/
	}
}

void SingleGame::getBlocksFallOnShipTopPoints(std::vector<Point> pointsAbove, std::set<int> &blocksIndexesAbove) {
	std::set<int> blocksIndexesAboveToCheck;
	std::vector<Point> nextPointsAboveBlocks;
	int pointsIndex, blocksIndex;
	bool found = false;

	if (pointsAbove.size() == 0) return;

	for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++, found = false) {
		for (pointsIndex = 0; pointsIndex < pointsAbove.size(); pointsIndex++) {
			if (blocks[blocksIndex].isBlockIncludesPoint(pointsAbove[pointsIndex])) {
				blocksIndexesAbove.insert(blocksIndex);
				blocksIndexesAboveToCheck.insert(blocksIndex);
			}
		}
	}
	nextPointsAboveBlocks = getPointsAboveBlocks(blocksIndexesAboveToCheck);
	getBlocksFallOnShipTopPoints(nextPointsAboveBlocks, blocksIndexesAbove);
}

std::vector<Point> SingleGame::getPointsAboveBlocks(std::set<int> blocksIndexesAbove) {
	std::vector<Point> points, temp;
	std::set<int>::iterator itr;

	for (itr = blocksIndexesAbove.begin(); itr != blocksIndexesAbove.end(); itr++) {
		temp = board.checkMoving(blocks[*itr].getPoints(), blocks[*itr].getSize(), blocks[*itr].getChar(), 0, -1);
		points.insert(points.end(), temp.begin(), temp.end());
	}

	return points;
}

//
bool SingleGame::checkBlockFallsOnShip(std::vector<Point> points, int blockSize) {
	int shipIndex;
	for (shipIndex = 0; shipIndex < 2; shipIndex++) {
		if ((ships[shipIndex].isShipIncludesSomePoints(points) &&
			blockSize > ships[shipIndex].getBlockSizeCapacity())
			&& !(ships[(shipIndex + 1) % 2].isShipIncludesSomePoints(points) &&
				blockSize <= ships[(shipIndex + 1) % 2].getBlockSizeCapacity())) {
			keepPlayingSingleGame = false;
			printLoseMessage("Your ship has been smashed by a block! ");
			return true;
		}
	}
	return false;
}

bool SingleGame::arePointsHaveChars(std::vector<Point> points, char* charsArr, int size) const {
	int i;
	for (i = 0; i < points.size(); i++) {
		if (isArrayIncludesChar(charsArr, size, points[i].getCh())) return true;
	}
	return false;
}

bool SingleGame::isArrayIncludesChar(char* arr, int size, char ch) const {
	int i;
	for (i = 0; i < size; i++) {
		if (arr[i] == ch) return true;
	}
	return false;
}

bool SingleGame::areAllPointsIncludeChar(std::vector<Point> points, char ch) const {
	int i;
	for (i = 0; i < points.size(); i++) {
		if (points[i].getCh() != ch) return false;
	}

	return true;
}