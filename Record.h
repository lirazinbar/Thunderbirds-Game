#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include "Files.h"
#include "Ship.h"
#include "StepSegment.h"

class GameScreen;

struct RecordArgumants {
	constexpr static const char* SAVE = "-save";
	constexpr static const char* LOAD = "-load";
	constexpr static const char* SILENT = "-silent";
};

typedef struct result {
	std::queue<int> deathTimePoints;
	int screenFinishTimePoint = -1;
} Result;

class Record {
private:
	std::vector<std::string> stepsFileNames;
	std::vector<std::string> resultFileNames;
	std::fstream stepsFile;
	std::fstream resultFile;
	int savedFileIndex = 0;
	std::queue<StepSegment> stepsQueue;
	Result resultData;
public:
	// Empty ctor
	Record();
	// Destructor - Closing the text files
	~Record() { stepsFile.close(), resultFile.close(); }
	// Return the steps txt file names as a string array
	const std::vector<std::string>& getRecordFilesNames() const { return stepsFileNames; }
	// Return the current number of the saved files
	int getSavedFileNumber() const { return savedFileIndex; };
	// Return the steps queue
	std::queue<StepSegment>& getQueue() { return stepsQueue; }
	// Change the savedFileIndex
	void setSavedFileIndex(int index) { savedFileIndex = index; }
	// Add a death point of time to resultData's queue
	void addDeathPointOfTime(int _deathTimePoints) { resultData.deathTimePoints.push(_deathTimePoints); }
	// Change the screenFinishTimePoint in resultData
	void setScreenFinishTimePoint(int _screenFinishTimePoint) { resultData.screenFinishTimePoint = _screenFinishTimePoint; }
	// Return screenFinishTimePoint
	int getsScreenFinishTimePoint() { return resultData.screenFinishTimePoint; }
	// Deletes all record files (steps and result) that were in the directory, before saving a new game
	void deleteRecordFiles();
	// Open the steps and result files for reading or writing
	void openFiles(OpenMode mode) {
		openFile(stepsFile, stepsFileNames[savedFileIndex], mode);
		openFile(resultFile, resultFileNames[savedFileIndex], mode);
	}
	// Search the names of the relevant files in pwd and return a vector taht stores them
	void getRecordFiles();
	// Opens the next steps and result text files in lexicographical order and load them
	void openNextSavedGameScreen(int screenNumber);
	// Load the saved screen game from files into a vector
	void readSavedGameScreen();
	// Save a screen game to files
	void writeSavedGameScreen(int screenNumber);
	// Write a step segment obj to the steps file
	void writeSegment(const StepSegment& segment);
	// Write the ghosts directions to a line
	void writeGhosts(const StepSegment& segment);
	// Read the data from result file
	void readResultFile();
	// Extract the next step segment from the steps queue
	bool extractStepSegment(StepSegment& segment);
	// Insert a step segment into the steps queue
	void insertStepSegment(StepSegment& segment, int pointOfTime, int key);
	// Return the next deathTimePoint
	int getNextDeathTimePoint();
	// Write the data to result file
	void writeResultFile();
	// Empty the steps and the death time queues
	void emptyQueues();
};