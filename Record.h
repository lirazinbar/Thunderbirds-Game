#pragma once

#include <vector>
#include <string>
#include <fstream>
#include <queue>
#include "Files.h"
#include "Ship.h"

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
public:
	class StepSegment {
		char pointOfTime = 0;
		/*int activeShip = int(ShipsIndex::BIG_SHIP);
		char activeShip = -1;
		char shipDirection = -1;*/
		char key = 0;
		std::vector<char> wanderingGhostsDirections{0};
		friend class Record;
	public:
		// Return pointOfTime
		int getPointOfTime() const { return pointOfTime; }
		// Return the key
		char getKey() const { return key; }
		// Return the wandering ghosts directions vector
		std::vector<char>& getGhostsVector() { return wanderingGhostsDirections; }
		// Change the pointOfTime
		void setPointOfTime(int _pointOfTim) { pointOfTime = _pointOfTim; }
		// Change the key
		void setKey(int _key) { key = _key; }
		// For the save mode ghosts vector
		void ghostsVectorResize(int size) { wanderingGhostsDirections.resize(size, 0); };
	};
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
	void openFiles(OpenMode mode) { openFile(stepsFile, stepsFileNames[savedFileIndex], mode), openFile(resultFile, resultFileNames[savedFileIndex], mode); }
	// Search the names of the relevant files in pwd and return a vector taht stores them
	void getRecordFiles();
	// Opens the next steps and result text files in lexicographical order and load them
	void openNextSavedGameScreen();
	// Load the saved screen game from files into a vector
	void readSavedGameScreen();
	// Save a screen game to files
	void writeSavedGameScreen();
	// Read a steps segment from a file into a StepSegment obj
	Record::StepSegment readSegment();
	// Write a step segment obj to the steps file
	void writeSegment(const StepSegment& segment);
	// Write the ghosts directions to a line
	void writeGhosts(const StepSegment& segment);
	// Read the ghosts directions from a line
	void readGhosts(StepSegment& tmpSegment);
	// Read the data from result file
	void readResultFile();
	// Extract the next step segment from the steps queue
	void extractStepSegment(StepSegment& segment);
	// Insert a step segment into the steps queue
	void insertStepSegment(StepSegment& segment, int pointOfTime, int key);
	// Return the next deathTimePoint
	int getNextDeathTimePoint();
	// Write the data to result file
	void writeResultFile();
	// Empty the steps and the death time queues
	void emptyQueues();
};