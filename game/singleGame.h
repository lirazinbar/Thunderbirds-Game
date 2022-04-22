#pragma once

#include "Board.h"
#include "Point.h"
#include "Ship.h"
#include "Block.h"
#include "Timer.h"
#include "Color.h"
#include "Game.h"
#include "GameScreen.h"
#include <set>
#include <iterator>
#include <algorithm>
#include <fstream>

class SingleGame {
	bool keepPlayingSingleGame = true;
	int screenNumber;
	Board board;
	Timer timer;
	Ship ships[2] = { {char(BoardSymbols::BIG_SHIP), 4, &board, 8}, {char(BoardSymbols::SMALL_SHIP), 2, &board, 20} }; // Index 0 is big ship and 1 is small ship
	int activeShip = int(ShipsIndex::BIG_SHIP);
	int blocksAmount;
	std::vector<Block> blocks;
	std::vector<HorizontalGhost> horizntalGhosts;
	int livesCount;
	Color color;
	int dirx = 0;
	int diry = 0;
public:
	// Ctor - get the lives count and prints the board
	SingleGame(int _livesCount, GameScreen& screen);
	// Destructor - If the player wins, exit the whole game. Otherwise, decrease one life
	~SingleGame();
	// Set the legend data member according to the chosen board
	void setLegend();
	// Set the two ships according to the chosen board
	void setShips();
	// Set the blocks according to the chosen board
	void setBlocks();
	// Set the ghosts according to the chosen board
	void setGhosts();
	// The function who run the single game - until exit, winning or lives decrease
	void play();
	// Takes action according to the player's key
	void assignKey(char& key);
	//Checks if time is up
	bool isTimeRanOut();
	// Pausing the gmae after hitting ESC
	void pauseGame();
	// Change teh current active ship (b - big, s - small)
	void changeActiveShip(ShipsIndex _activeShip);
	// Checks if the player won the game (Both ships have reached the end point)
	bool isGameWon();
	// Moving the ships
	void moveShip();
	// Checks if the ship can push the block(s)
	void checkShipPushBlock(std::vector<Point> points);
	// get only the blocks above that the ship is not collide with
	std::set<int> getOnlyBlocksAboveToMove(std::set<int> blocksAbove, std::set<int> blocksIndexesToMove);
	// Return all the blocks indexes in "blocks" array which can move after a ship pushed them
	std::set<int> getBlocksCanMoveAfterCollideByShip(std::vector<Point> points, bool& canMove, bool& isColide, std::set<int>& blocksAbove);
	// get all the blocks above the points recursive
	std::set<int> getAllBlocksAbovePoints(std::vector<Point> points);
	// Clculate the total size of all the blocks in "blocksIndexesToMove"
	int getTotalSizeOfBlocks(std::set<int> blocksIndexesToMove) const;
	// Return the collision points of the blocks in "blocksIndexesToMove",
	// The points which are not BLANK or the points char itself
	std::vector<Point> getTheNextCollisionPointsOfBlocks(std::set<int> blocksIndexesToMove, int _dirx, int _diry);
	// Move the blocks in "blocksToMove"
	void checkBlocksAboveAndMove(std::set<int> blocksIndexesToMove);
	// Move all the blocks vertically, "Free fall"
	void checkBlocksVerticalMove();
	// check if the blocks smash ship
	void checkBlocksSmashShips(std::set<int> blocksToCheck);
	// get all the blocks can move vertically recursive
	std::set<int> getBlocksCanMoveVertical(std::vector<Point> points, bool& canMove, bool& isColide);
	// Move the blocks in "blocksIndexesToMove" on screen according to dirx, diry
	void moveBlocks(std::set<int> blocksIndexesToMove, int dirx, int diry);
	// Chceks if the block can move on board
	bool isBlockCanMove(int blockIndex);
	// Checks if there are block above the ships and move the accordingly
	void checkBlocksAboveShip(std::vector<Point> adjacentShipPoints);
	// get the blocks that fall on ship recursive
	void getBlocksFallOnShipTopPoints(std::vector<Point> points, std::set<int>& blocksIndexesAbove, int shipIndex);
	// get all the points above the blocksIndexes
	std::vector<Point> getPointsAboveBlocks(std::set<int> blocksIndexesAbove);
	// Return true of all the points have ch
	bool areAllPointsIncludeChar(std::vector<Point> points, char ch) const;
	// Checks if the points have the chars in charsArr
	bool arePointsHaveChars(std::vector<Point> points, char* charsArr, int size) const;;
	// Return true of all the points have chars
	bool areAllPointsIncludeChars(std::vector<Point> points, char* charsArr, int size) const;
	// Moves all the horizontal ghosts
	void moveGhosts();
	// Deletes the ghosts that include the points
	void deleteGhosts(std::vector<Point> points);
	// Move ghots that moving blocks are collide with
	void moveGhostAfterCollide(std::vector<Point> points);
	// Returns true if thw blocks include the given point
	bool areBlocksIncludePoint(Point p);
	// Prints the ships on screen
	void printShips();
	// Prints the blocks on screen
	void printBlocks();
};