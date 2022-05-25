#include "Record.h"
#include "GameScreen.h"
#include "Files.h"
#include "Game.h"
#include <filesystem>

Record::Record() {
	if (Game::getMainGameMode() == GameMode::SAVE)
		deleteRecordFiles();
}

void Record::deleteRecordFiles() {
	std::vector<std::string> RecordFileNames;

	getRelevantFiles(RecordFileNames, FileSuffix::STEPS);
	getRelevantFiles(RecordFileNames, FileSuffix::RESULT);;
	for (int i = 0; i < RecordFileNames.size(); i++) {
		remove(RecordFileNames[i].c_str());
	}
}

void Record::getRecordFiles() {
	getRelevantFiles(stepsFileNames, FileSuffix::STEPS);
	getRelevantFiles(resultFileNames, FileSuffix::RESULT);
	// Checking if the number of steps and result are equal, and not zero
	if (stepsFileNames.size() != resultFileNames.size() || stepsFileNames.size() == 0) {
		std::cout << "There are missing record files. Can't load the game." << std::endl;
		Game::stopPlaying();
	}
}

void Record::openNextSavedGameScreen() {
	if (Game::getMainGameMode() == GameMode::SAVE)
		writeSavedGameScreen();
	// If there is another screen to play
	if (Game::getGameWinningStatus() == false)
		savedFileIndex++;

	// Reset steps and death points queues and screen finish point
	emptyQueues();
	resultData.screenFinishTimePoint = -1;

	if (Game::getMainGameMode() == GameMode::LOAD)
		readSavedGameScreen();
}

void Record::readSavedGameScreen() {
	openFiles(OpenMode::READ);

	// Read steps file until end of file, line by line
	while (!stepsFile.eof()) {
		StepSegment tmpSegment = readSegment();
		//ss << line;
		//ss >> tmpSegment.pointOfTime;
		//std::getline(stepsFile, line)
		//ss >> tmpChar;
		//// Ship direction or active ship change
		//if (tmpChar == 'k')
		//	ss >> tmpSegment.key;
		//// Wandering ghosts direction change
		//if (tmpChar == 'g') {
		//	while (!ss.eof()) {
		//		ss >> tmpChar;
		//		tmpSegment.wanderingGhostsDirections.push_back(tmpChar);
		//	}
		//}
		//stepsArr.push_back(tmpSegment);
		stepsQueue.push(tmpSegment);
	}
	readResultFile();
	stepsFile.close(), resultFile.close();
}

Record::StepSegment Record::readSegment() {
	std::stringstream ss;
	std::string line;
	StepSegment tmpSegment;
	char tmpChar;

	tmpSegment.pointOfTime = stepsFile.get();
	stepsFile.ignore(256, '\n');
	tmpChar = stepsFile.get();
	if (tmpChar != '\n') {
		tmpSegment.key = tmpChar;
		stepsFile.ignore(256, '\n');
	}
	readGhosts(tmpSegment);
	return tmpSegment;
}

void Record::readGhosts(StepSegment& tmpSegment) {
	std::string line;
	std::stringstream ss;
	char tmpChar;

	std::getline(stepsFile, line);
	ss << line;
	while (!ss.eof()) {
		ss >> tmpChar;
		tmpSegment.wanderingGhostsDirections.push_back(tmpChar);
	}
}

void Record::readResultFile() {
	std::string line;
	std::stringstream ss;
	char tmpChar;

	// Read deathTimePoints
	std::getline(stepsFile, line);
	ss << line;
	while (!ss.eof()) {
		ss >> tmpChar;
		resultData.deathTimePoints.push(tmpChar);
	}
	// Read screenFinishTimePoint. -1 if the player didn't finish the screen
	resultData.screenFinishTimePoint = stepsFile.get();
}

void Record::writeSavedGameScreen() {
	openFiles(OpenMode::WRITE);
	StepSegment tmpSegment;

	while (!stepsQueue.empty()) {
		tmpSegment = stepsQueue.front();
		stepsQueue.pop();
		writeSegment(tmpSegment);
	}
	readResultFile();
	stepsFile.close(), resultFile.close();
}

void Record::writeSegment(const StepSegment& segment) {
	std::stringstream ss;
	std::string line;

	stepsFile.put(segment.pointOfTime);
	stepsFile << std::endl;
	if (segment.key != 0)
		stepsFile.put(segment.key);
	stepsFile << std::endl;
	writeGhosts(segment);
	stepsFile << std::endl;
}

void Record::writeGhosts(const StepSegment& segment) {
	for (int i = 0; i < segment.wanderingGhostsDirections.size(); i++) {
		stepsFile << segment.wanderingGhostsDirections[i] << ' ';
	}
}

void Record::writeResultFile() {
	int tmpDeathPoint;

	// Write deathTimePoints
	while (!resultData.deathTimePoints.empty()) {
		tmpDeathPoint = resultData.deathTimePoints.front();
		resultData.deathTimePoints.pop();
		resultFile << tmpDeathPoint << ' ';
	}
	resultFile << std::endl;
	// Write screenFinishTimePoint. -1 if the player didn't finish the screen
	resultFile << resultData.screenFinishTimePoint;
}

void Record::extractStepSegment(StepSegment& segment) {
	if (!stepsQueue.empty()) {
		segment = stepsQueue.front();
		stepsQueue.pop();
	}
	else
		printGameLoadError();
}

void Record::insertStepSegment(StepSegment& segment, int pointOfTime, int key) {
	segment.setPointOfTime(pointOfTime);
	segment.setKey(key);
	stepsQueue.push(segment);
}

int Record::getNextDeathTimePoint() {
	int point = 0;

	if (!resultData.deathTimePoints.empty()) {
		point = resultData.deathTimePoints.front();
		resultData.deathTimePoints.pop();
	}
	else
		printGameLoadError();
	return point;
}

void Record::emptyQueues() {
	std::queue<StepSegment> emptySegmentQueue;
	std::queue<int> emptyDeathTimePointsQueue;

	std::swap(stepsQueue, emptySegmentQueue);
	std::swap(resultData.deathTimePoints, emptyDeathTimePointsQueue);
}