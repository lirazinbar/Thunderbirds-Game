#include <conio.h>
#include <cctype>
#include <windows.h>
#include "SingleGame.h"
#include "Utils.h"
#include "Timer.h"
#include "Record.h"

SingleGame::SingleGame(int _livesCount, GameScreen& screen): livesCount(_livesCount),
											screenNumber(screen.getScreenNumber()) {
	screen.load(board, timer);
	setLegend();
	setShips();
	setBlocks();
	setGhosts();
	board.print(activeShip, timer.getTimeLeft(), livesCount, screenNumber);
	printShips();
	printBlocks();
}

SingleGame::~SingleGame() {
	clrscr();
	Game::decreseLives();
}

void SingleGame::setLegend() {
	// Searching for the legend location on board and set it
	Point legendLocation = board.findCharOnBoard(char(BoardSymbols::LEGEND));
	board.getLegend().setLegendLocation(legendLocation);
}

void SingleGame::setShips() {
	for (size_t i = 0; i < 2; i++) {
		ships[i].setShip();
	}
}

void SingleGame::setBlocks() {
	blocks = board.loadBlocksRec();
	blocksAmount = blocks.size();
}

void SingleGame::setGhosts() {
	ghosts = board.loadGhosts();
}

void SingleGame::printShips() {
	int i;
	for (i = 0; i < 2; i++) {
		ships[i].drawOnScreen();
	}
}

void SingleGame::printBlocks() {
	int i;
	for (i = 0; i < blocksAmount; i++) {
		blocks[i].drawOnScreen();
	}
}

int SingleGame::play(Record& gameRecord) {
	char key = 0;
	int pointOfTimeCounter = 0;
	std::vector<int> emptyVec;
	StepSegment currSegment;
	int modeSleep = getModeSleepTime();
	
	while (keepPlayingSingleGame == true) {
		key = ' ';
		pointOfTimeCounter++;

		if (Game::getMainGameMode() == GameMode::LOAD) {
			if (currSegment.getKey() == Keys::FINISH_FILE) {
				keepPlayingSingleGame = false;
				setAndCheckResultFile(gameRecord, pointOfTimeCounter - 1);
				return -1;
			}
			else {
				if (currSegment.getPointOfTime() < pointOfTimeCounter)
					if (!gameRecord.extractStepSegment(currSegment)) return -1;
				if (currSegment.getPointOfTime() == pointOfTimeCounter) {
					key = currSegment.getKey();
					assignKey(key);
				}
			}
		}
		else if (_kbhit()) {
			key = _getch();
			assignKey(key);
		}
		moveGhosts(currSegment.getGhostsVector());
		moveShip(currSegment.getGhostsVector());
		checkBlocksVerticalMove();
		Sleep(modeSleep);
		timer.tick();
		if (isTimeRanOut() || isGameWon()) {
			keepPlayingSingleGame = false;
		}
		if (key == Keys::ESC) {
			key = ' ';
			if (!keepPlayingSingleGame) key = Keys::FINISH_FILE;
		}
		if (Game::getMainGameMode() == GameMode::SAVE)
			gameRecord.insertStepSegment(currSegment, pointOfTimeCounter, key);
	}

   	setAndCheckResultFile(gameRecord, pointOfTimeCounter);
	return pointOfTimeCounter;
}


void SingleGame::setAndCheckResultFile(Record& gameRecord, int pointOfTime) {
	if (Game::getMainGameMode() == GameMode::SAVE) {
		if (isGameWon()) {
			gameRecord.setScreenFinishTimePoint(pointOfTime);
		}
		else {
			gameRecord.addDeathPointOfTime(pointOfTime);
		}
	}

	else if (Game::getMainGameMode() == GameMode::LOAD) {
		if (isGameWon()) {
			if (Game::getSecondaryGameMode() == GameMode::SILENT) {
				if (gameRecord.getsScreenFinishTimePoint() != pointOfTime) {
					printFailTest();
				}
				else printPassTest();
			}
			else {
				if (gameRecord.getsScreenFinishTimePoint() != pointOfTime) {
					printGameResultError("result finish point time - " + std::to_string(gameRecord.getsScreenFinishTimePoint()) 
						+ ", actual point of time - " + std::to_string(pointOfTime));
				}
			}
		}
		else {
			int deathPoint = gameRecord.getNextDeathTimePoint();
			if (Game::getSecondaryGameMode() == GameMode::SILENT) {
				if (deathPoint != pointOfTime) {
					printFailTest();
				}
				else printPassTest();
			}
			else if (deathPoint != pointOfTime) {
				printGameResultError("result death point time - " + std::to_string(deathPoint)
					+ ", actual point of time - " + std::to_string(pointOfTime));
			}
		}
	}
}

void SingleGame::assignKey(char& key) {
	switch (std::tolower(key)) {
	case Keys::ESC:
		dirx = diry = 0;
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
	//if (timer.getDeltaTime() >= 1000) {
	//	timer.reduceTimeLeft();
		board.getLegend().printTimer(timer.getTimeLeft());
		// timer.resetTickStartTime();
		// if time runs out
		if (timer.getTimeLeft() <= 0) {
			printLoseMessage("Time is up!");
			return true;
		}
	// }
	return false;
};

void SingleGame::pauseGame() {
	char key = 0;

	clrscr();
	gotoxy(10, 10);
	std::cout << "Game paused, press ESC again to continue or 9 to Exit" << std::endl;
	while (key != Keys::Exit && key != Keys::ESC) {
		if (_kbhit()) {
			key = _getch();
		}
		if (key == Keys::Exit) {
			keepPlayingSingleGame = false;
			Game::stopPlaying();
			clrscr();
		}
		else if (key == Keys::ESC) {
			clrscr();
			board.print(activeShip, timer.getTimeLeft(), livesCount, screenNumber);
			printShips();
			printBlocks();
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
		Game::setGameWinningStatus(true);
		printWinMessage(false);
	}
	return Game::getGameWinningStatus();
}

void SingleGame::moveGhosts(std::vector<int>& ghostsDirections) {
	if (Game::getMainGameMode() != GameMode::LOAD) ghostsDirections.clear();
	std::vector<Ghost*>::iterator itr = ghosts.begin();
	char currentPointCh, nextPointCh;
	Point p;
	int index = 0;

	while (itr != ghosts.end()) {
		if ((*itr)->getType() == GhostsTypes::WANDERING_GHOST_TYPE && Game::getMainGameMode() == GameMode::LOAD) {
			if (index < ghostsDirections.size()) {
				(*itr)->setDir(ghostsDirections[index]);
			}
		}
		p = (*itr)->getNextPointToMove();
		currentPointCh = board.get((*itr)->getPoint());
		nextPointCh = board.get(p);
		if (currentPointCh == (char)BoardSymbols::BIG_SHIP || currentPointCh == (char)BoardSymbols::SMALL_SHIP
			|| nextPointCh == (char)BoardSymbols::BIG_SHIP || nextPointCh == (char)BoardSymbols::SMALL_SHIP) {
			// kill ships
			keepPlayingSingleGame = false;
			printLoseMessage("Your ship has been killed by a ghost! ");
			if (Game::getMainGameMode() == GameMode::SAVE) ghostsDirections.push_back((*itr)->getDir());
			return;
		}
		if (areBlocksIncludePoint((*itr)->getPoint())) {
			itr = ghosts.erase(itr);
		}
		else if ((*itr)->getType() == GhostsTypes::WANDERING_GHOST_TYPE && Game::getMainGameMode() == GameMode::LOAD) {
			if (index < ghostsDirections.size()) {
				(*itr)->setDir(ghostsDirections[index]);
				(*itr)->move();
			}
			++itr;
		}		
		else {
			if (nextPointCh != (char)BoardSymbols::BLANK) {
				(*itr)->changeDir();
				if (Game::getMainGameMode() == GameMode::SAVE) ghostsDirections.push_back(0);
			}
			else {
				// TODO
				if (Game::getMainGameMode() == GameMode::SAVE) ghostsDirections.push_back((*itr)->getDir());

				/*if ((*itr)->getType() == GhostsTypes::WANDERING_GHOST_TYPE) {
					if (Game::getMainGameMode() == GameMode::LOAD) {
						if (index < ghostsDirections.size()) (*itr)->setDir(ghostsDirections[index]);
					}
					else {*/
				/*if (Game::getMainGameMode() == GameMode::SAVE)
					ghostsDirections.push_back(0);*/
					/*}
				}*/
				(*itr)->move();
			}
			++itr;
		}
		++index;
	}
}

void SingleGame::moveGhostAfterCollide(const std::vector<Point>& points, std::vector<int>& ghostsDirections) {
	int index = 0;
	std::vector<Ghost*>::iterator itr = ghosts.begin();
	int indexToMove;
	Point p;
	char ch;
	while (itr != ghosts.end()) {
		indexToMove = (*itr)->isGhostExistInPointsVec(points);
		if (indexToMove != -1) {
			(*itr)->setDir(dirx, diry);
			p = (*itr)->getNextPointToMove();
			ch = board.get(p);
			if (ch == (char)BoardSymbols::BIG_SHIP || ch == (char)BoardSymbols::SMALL_SHIP) {
				// kill ships
				keepPlayingSingleGame = false;
				printLoseMessage("Your ship has been killed by a ghost! ");
				return;
			}
			if (ch != (char)BoardSymbols::BLANK || (*itr)->getType() == GhostsTypes::WANDERING_GHOST_TYPE) {
				itr = ghosts.erase(itr);
				points[indexToMove].deleteFromScreen();
			}
			else {
				// TODO - kill wandering
				/*if ((*itr)->getType() == GhostsTypes::WANDERING_GHOST_TYPE) {
					itr = ghosts.erase(itr);
					points[indexToMove].deleteFromScreen();
				}*/
				/*if (Game::getMainGameMode() == GameMode::LOAD) {
					if (index < ghostsDirections.size()) (*itr)->setDir(ghostsDirections[index]);
				}
				else {
					ghostsDirections[index] = ((*itr)->getDir());
				}*/
				(*itr)->move();
				// TODO
				/*(*itr)->move();
				ghostsDirections[index]=((*itr)->getDir());*/
				++itr;
			}
		}
		else {
			++itr;
		}
		++index;
	}
}

void SingleGame::deleteGhosts(const std::vector<Point>& points) {
	std::vector<Ghost*>::iterator itr = ghosts.begin();
	int indexToRem;
	while (itr != ghosts.end()) {
		indexToRem = (*itr)->isGhostExistInPointsVec(points);
		if (indexToRem != -1) {
			itr = ghosts.erase(itr);
			points[indexToRem].deleteFromScreen();
		}
		else ++itr;
	}
}

void SingleGame::moveShip(std::vector<int>& ghostsDirections) {
	// If there is no change in direction
	if (dirx == 0 && diry == 0) return;
	// Get the points that will collide with another object
	std::vector<Point> points = board.checkMoving(ships[activeShip].getPoints(), ships[activeShip].getSize(), ships[activeShip].getChar(), dirx, diry);

	// If the ships doesn't collide with anything
	if (points.size() == 0) {
		checkBlocksAboveShip(ships[activeShip].getAboveShipPoints(), ghostsDirections);
		return;
	}
	// Check collision with wall & ships
	char collisionChars[2] = { (char)BoardSymbols::WALL, ships[(activeShip + 1) % 2].getChar() };
	if (arePointsHaveChars(points, collisionChars, 2)) {
		dirx = diry = 0;
		return;
	}
	if (areAllPointsIncludeChar(points, (char)BoardSymbols::HORIZONTAL_GHOST) ||
		areAllPointsIncludeChar(points, (char)BoardSymbols::VERTICAL_GHOST) ||
		areAllPointsIncludeChar(points, (char)BoardSymbols::WANDERING_GHOST)) {
		// kill ships
		keepPlayingSingleGame = false;
		printLoseMessage("Your ship has been killed by a ghost! ");
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
	checkShipPushBlock(points, ghostsDirections);
}

void SingleGame::checkShipPushBlock(std::vector<Point>& points, std::vector<int>& ghostsDirections) {
	bool canMove, isColide;
	std::set<int> blocksAbove, blocksAboveToMove, blocksAboveBlocks, allBlocksToMove, blocksAboveShip;
	// get all the blocks the ship collide with + the blocks above them to carry
	std::set<int> blocksIndexesToMove = getBlocksCanMoveAfterCollideByShip(points, canMove, isColide, blocksAboveBlocks, ghostsDirections);

	// get all the blocks above the ship
	blocksAboveShip = getAllBlocksAbovePoints(ships[activeShip].getAboveShipPoints());
	std::set_union(blocksAboveShip.begin(), blocksAboveShip.end(), blocksAboveBlocks.begin(), blocksAboveBlocks.end(), std::inserter(blocksAbove, blocksAbove.begin()));
	blocksAboveToMove = getOnlyBlocksAboveToMove(blocksAbove, blocksIndexesToMove);

	// get all the blocks to move and calc their size
	std::set_union(blocksAboveToMove.begin(), blocksAboveToMove.end(), blocksIndexesToMove.begin(), blocksIndexesToMove.end(), std::inserter(allBlocksToMove, allBlocksToMove.begin()));
	int totalSize = getTotalSizeOfBlocks(allBlocksToMove);

	if (!canMove || totalSize > ships[activeShip].getBlockSizeCapacity()) {
		dirx = diry = 0;
		return;
	}

	if (isColide) {
		moveBlocks(blocksIndexesToMove, dirx, diry);
		// move blocks above after checking if they can move
		checkBlocksAboveAndMove(blocksAboveToMove, ghostsDirections);
	}
}

std::set<int> SingleGame::getOnlyBlocksAboveToMove(std::set<int> blocksAbove, std::set<int> blocksIndexesToMove) {
	std::set<int> blocksAboveToMove;
	std::set<int>::iterator itr;

	for (itr = blocksAbove.begin(); itr != blocksAbove.end(); itr++) {
		if (!isExistInSet(blocksIndexesToMove, *itr)) blocksAboveToMove.insert(*itr);
	}

	return blocksAboveToMove;
}

std::set<int> SingleGame::getBlocksCanMoveAfterCollideByShip(const std::vector<Point>& points, bool& canMove, bool& isColide, std::set<int>& blocksAbove, std::vector<int>& ghostsDirections) {
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
	if (areAllPointsIncludeChar(points, (char)BoardSymbols::HORIZONTAL_GHOST) ||
		areAllPointsIncludeChar(points, (char)BoardSymbols::VERTICAL_GHOST) ||
		areAllPointsIncludeChar(points, (char)BoardSymbols::WANDERING_GHOST)) {
		moveGhostAfterCollide(points, ghostsDirections);
	}

	// get the blocks that the points are collide with
	for (pointsIndex = 0; pointsIndex < points.size(); pointsIndex++) {
		for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++) {
			if (blocks[blocksIndex].isBlockIncludesPoint(points[pointsIndex])) { // the point is collide with the block
				isColide = true;
				blocksIndexesToMove.insert(blocksIndex);
				// get blocks above recursive
				collisionPointsAbove = getTheNextCollisionPointsOfBlocks({ blocksIndex }, 0, -1);
				tempBlocks = getAllBlocksAbovePoints(collisionPointsAbove);
				std::set_union(blocksAbove.begin(), blocksAbove.end(), tempBlocks.begin(), tempBlocks.end(), std::inserter(blocksAbove, blocksAbove.begin()));
			}
		}
	}

	allCollisionPoints = getTheNextCollisionPointsOfBlocks(blocksIndexesToMove, dirx, diry);
	nextBlocksIndexesToMove = getBlocksCanMoveAfterCollideByShip(allCollisionPoints, canMove, isColide, blocksAbove, ghostsDirections);

	if (canMove) {
		std::set<int> newSet;
		std::set_union(blocksIndexesToMove.begin(), blocksIndexesToMove.end(), nextBlocksIndexesToMove.begin(), nextBlocksIndexesToMove.end(), std::inserter(newSet, newSet.begin()));
		return newSet;
	}

	std::set<int> emptySet;
	return emptySet;
}

std::set<int> SingleGame::getAllBlocksAbovePoints(const std::vector<Point>& points) {
	int blocksIndex, pointsIndex;
	std::set<int> blocksIndexesToMove, nextBlocksIndexesToMove;
	std::vector<Point> allCollisionPoints;

	// if all points are not collide return null set - blocksIndexesToMove;
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
				// get blocks above recursively 
			}
		}
	}

	allCollisionPoints = getTheNextCollisionPointsOfBlocks(blocksIndexesToMove, 0, -1);
	nextBlocksIndexesToMove = getAllBlocksAbovePoints(allCollisionPoints);


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

void SingleGame::checkBlocksAboveAndMove(std::set<int> blocksIndexesToMove, std::vector<int>& ghostsDirections) {
	bool canMove, isColide;
	std::set<int> blocksAbove, getblocksToMove, movedBlocks, blocksAboveNotToMove, checkedBlocks, blocksToMove, temp;
	std::set<int>::iterator itr;
	int totalSizeOfBlocks;

	ships[activeShip].deleteFromScreen();

	totalSizeOfBlocks = getTotalSizeOfBlocks(blocksIndexesToMove);

	if (totalSizeOfBlocks <= ships[activeShip].getBlockSizeCapacity()) {
		for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
			if (!isExistInSet(checkedBlocks, *itr)) {
				getblocksToMove = getBlocksCanMoveAfterCollideByShip(blocks[*itr].getPoints(), canMove, isColide, blocksAbove, ghostsDirections);
				if (canMove) {
					std::set_union(getblocksToMove.begin(), getblocksToMove.end(), movedBlocks.begin(), movedBlocks.end(), std::inserter(movedBlocks, movedBlocks.begin()));
				}
				else {
					temp = getAllBlocksAbovePoints(getTheNextCollisionPointsOfBlocks({ *itr }, 0, -1));
					std::set_union(temp.begin(), temp.end(), checkedBlocks.begin(), checkedBlocks.end(), std::inserter(checkedBlocks, checkedBlocks.begin()));
					std::set_union(temp.begin(), temp.end(), blocksAboveNotToMove.begin(), blocksAboveNotToMove.end(), std::inserter(blocksAboveNotToMove, blocksAboveNotToMove.begin()));
				}
				std::set_union(getblocksToMove.begin(), getblocksToMove.end(), checkedBlocks.begin(), checkedBlocks.end(), std::inserter(checkedBlocks, checkedBlocks.begin()));
			}
		}
	}

	blocksToMove = reduceSets(movedBlocks, blocksAboveNotToMove);

	totalSizeOfBlocks = getTotalSizeOfBlocks(blocksToMove);
	if (totalSizeOfBlocks <= ships[activeShip].getBlockSizeCapacity())
		moveBlocks(blocksToMove, dirx, diry);


	ships[activeShip].setPointsIndexes(dirx, diry);
	ships[activeShip].drawOnScreen();
}

void SingleGame::checkBlocksVerticalMove() {
	bool canMove, isColide;
	std::set<int> getblocksToMove, checkedBlocks, blocksToCheck;
	int i;

	for (i = 0; i < blocks.size(); i++) {
		if (!isExistInSet(checkedBlocks, i)) {
			getblocksToMove = getBlocksCanMoveVertical(blocks[i].getPoints(), canMove, isColide);
			if (canMove) {
				moveBlocks(getblocksToMove, 0, 1);
				std::set_union(getblocksToMove.begin(), getblocksToMove.end(), checkedBlocks.begin(), checkedBlocks.end(), std::inserter(checkedBlocks, checkedBlocks.begin()));
			}
			if (isColide) {
				std::set_union(getblocksToMove.begin(), getblocksToMove.end(), blocksToCheck.begin(), blocksToCheck.end(), std::inserter(blocksToCheck, blocksToCheck.begin()));
			}
		}
	}
	if (blocksToCheck.size())
		checkBlocksSmashShips(blocksToCheck);
}

void SingleGame::checkBlocksSmashShips(std::set<int> blocksToCheck) {
	int totalSizeSmall, totalSizeBig, totalSizeOfBlocks;
	std::set<int> blocksIndexesAboveSmall, blocksIndexesAboveBig, allSmallBlocks, allBigBlocks, smallCheck, bigCheck, SmallAndBigBlocks;

	getBlocksFallOnShipTopPoints(ships[1].getAboveShipPoints(), blocksIndexesAboveSmall, 1);
	getBlocksFallOnShipTopPoints(ships[0].getAboveShipPoints(), blocksIndexesAboveBig, 0);

	allSmallBlocks = getIndexesInBothSets(blocksIndexesAboveSmall, blocksToCheck);
	allBigBlocks = getIndexesInBothSets(blocksIndexesAboveBig, blocksToCheck);

	smallCheck = reduceSets(allSmallBlocks, allBigBlocks);
	bigCheck = reduceSets(allBigBlocks, allSmallBlocks);

	std::set_union(allSmallBlocks.begin(), allSmallBlocks.end(), allBigBlocks.begin(), allBigBlocks.end(), std::inserter(SmallAndBigBlocks, SmallAndBigBlocks.begin()));

	totalSizeOfBlocks = getTotalSizeOfBlocks(SmallAndBigBlocks);
	totalSizeSmall = getTotalSizeOfBlocks(smallCheck);
	totalSizeBig = getTotalSizeOfBlocks(bigCheck);

	if (totalSizeOfBlocks > ships[0].getBlockSizeCapacity() + ships[1].getBlockSizeCapacity() ||
		totalSizeSmall > ships[1].getBlockSizeCapacity() ||
		totalSizeBig > ships[0].getBlockSizeCapacity()) {
		keepPlayingSingleGame = false;
		printLoseMessage("Your ship has been smashed by a block! ");
	}
}

std::set<int> SingleGame::getBlocksCanMoveVertical(const std::vector<Point>& points, bool& canMove, bool& isColide) {
	int blocksIndex, pointsIndex;
	std::set<int> blocksIndexesToMove, nextBlocksIndexesToMove, tempBlocks;
	std::vector<Point> allCollisionPoints, collisionPointsAbove;
	isColide = false;

	// if all points are not collide return null set - blocksIndexesToMove;
	if (areAllPointsIncludeChar(points, ' ')) {
		canMove = true;
		return blocksIndexesToMove;
	}

	// if one of the points colides with wall return is colide-true, and canMove-false, or the other ship
	char wall[1] = { (char)BoardSymbols::WALL };
	if (arePointsHaveChars(points, wall, 1)) {
		isColide = false;
		canMove = false;
		return blocksIndexesToMove;
	}

	char shipsChars[2] = { ships[0].getChar(), ships[1].getChar() };
	if (arePointsHaveChars(points, shipsChars, 2)) {
		isColide = true;
		canMove = false;
		return blocksIndexesToMove;
	}

	if (areAllPointsIncludeChar(points, (char)BoardSymbols::HORIZONTAL_GHOST)
		|| areAllPointsIncludeChar(points, (char)BoardSymbols::VERTICAL_GHOST)
		|| areAllPointsIncludeChar(points, (char)BoardSymbols::WANDERING_GHOST)) {
		deleteGhosts(points);
		canMove = true;
		return blocksIndexesToMove;
	}

	// get the blocks that the points are collide with
	for (pointsIndex = 0; pointsIndex < points.size(); pointsIndex++) {
		for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++) {
			if (blocks[blocksIndex].isBlockIncludesPoint(points[pointsIndex])) { // the point is collide with the block
				isColide = true;
				blocksIndexesToMove.insert(blocksIndex);
			}
		}
	}

	allCollisionPoints = getTheNextCollisionPointsOfBlocks(blocksIndexesToMove, 0, 1);
	nextBlocksIndexesToMove = getBlocksCanMoveVertical(allCollisionPoints, canMove, isColide);

	std::set<int> newSet;

	std::set_union(blocksIndexesToMove.begin(), blocksIndexesToMove.end(), nextBlocksIndexesToMove.begin(), nextBlocksIndexesToMove.end(), std::inserter(newSet, newSet.begin()));

	return newSet;
}

void SingleGame::moveBlocks(std::set<int> blocksIndexesToMove, int _dirx, int _diry) {
	std::set<int>::iterator itr;

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		blocks[*itr].deleteFromScreen();
	}

	for (itr = blocksIndexesToMove.begin(); itr != blocksIndexesToMove.end(); itr++) {
		blocks[*itr].setPointsIndexes(_dirx, _diry);
		blocks[*itr].drawOnScreen();
	}
}

bool SingleGame::isBlockCanMove(int blockIndex) {
	std::vector<Point> collisionPoints = board.checkMoving(blocks[blockIndex].getPoints(),
		blocks[blockIndex].getSize(), blocks[blockIndex].getChar(), dirx, diry);
	return (collisionPoints.size() == 0 || areAllPointsIncludeChar(collisionPoints, ships[activeShip].getChar()));
}

void SingleGame::checkBlocksAboveShip(const std::vector<Point>& aboveShipPoints, std::vector<int>& ghostsDirections) {
	std::set<int> blocksAbove = getAllBlocksAbovePoints(aboveShipPoints);
	if (blocksAbove.size() == 0) {
		ships[activeShip].move(dirx, diry);
		return;
	}

	checkBlocksAboveAndMove(blocksAbove, ghostsDirections);
}

void SingleGame::getBlocksFallOnShipTopPoints(const std::vector<Point>& pointsAbove, std::set<int>& blocksIndexesAbove, int shipIndex) {
	std::set<int> blocksIndexesAboveToCheck;
	std::vector<Point> nextPointsAboveBlocks;
	int pointsIndex, blocksIndex;
	bool found = false;

	// TODO
	if (pointsAbove.size() == 0 ||
		areAllPointsIncludeChar(pointsAbove, (char)BoardSymbols::WALL) ||
		areAllPointsIncludeChar(pointsAbove, (char)BoardSymbols::END_POINT) ||
		areAllPointsIncludeChar(pointsAbove, ships[(shipIndex + 1) % 2].getChar())) return;


	for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++, found = false) {
		for (pointsIndex = 0; pointsIndex < pointsAbove.size(); pointsIndex++) {
			if (blocks[blocksIndex].isBlockIncludesPoint(pointsAbove[pointsIndex])) {
				blocksIndexesAbove.insert(blocksIndex);
				blocksIndexesAboveToCheck.insert(blocksIndex);
			}
		}
	}
	nextPointsAboveBlocks = getPointsAboveBlocks(blocksIndexesAboveToCheck);
	getBlocksFallOnShipTopPoints(nextPointsAboveBlocks, blocksIndexesAbove, shipIndex);
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

bool SingleGame::areAllPointsIncludeChar(const std::vector<Point>& points, char ch) const {
	int i;
	for (i = 0; i < points.size(); i++) {
		if (points[i].getCh() != ch) return false;
	}

	return true;
}

bool SingleGame::arePointsHaveChars(const std::vector<Point>& points, char* charsArr, int size) const {
	int i;
	for (i = 0; i < points.size(); i++) {
		if (isArrayIncludesChar(charsArr, size, points[i].getCh())) return true;
	}
	return false;
}

bool SingleGame::areAllPointsIncludeChars(const std::vector<Point>& points, char* charsArr, int size) const {
	int i;
	for (i = 0; i < points.size(); i++) {
		if (!isArrayIncludesChar(charsArr, size, points[i].getCh())) return false;
	}

	return true;
}

bool SingleGame::areBlocksIncludePoint(Point p) {
	int blocksIndex;
	for (blocksIndex = 0; blocksIndex < blocksAmount; blocksIndex++) {
		if (blocks[blocksIndex].isBlockIncludesPoint(p)) { // the point is collide with the block
			return true;
		}
	}

	return false;
}

int SingleGame::getModeSleepTime() {
	// Load + Silent modes
	int modeSleep = 100;
	if (Game::getMainGameMode() == GameMode::LOAD){
		modeSleep = 50;
		if (Game::getSecondaryGameMode() == GameMode::SILENT) {
			modeSleep = 0;
		}
	}
	return modeSleep;
}
