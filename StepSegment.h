#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <filesystem>

class StepSegment {
	int pointOfTime = 0;
	char key = 0;
	std::vector<int> wanderingGhostsDirections{ 0 };
	friend class Record;
public:
	StepSegment() {};
	StepSegment(int _pointOfTime, char _key, std::vector<int>& _wanderingGhostsDirections) : pointOfTime(_pointOfTime), key(_key), wanderingGhostsDirections(_wanderingGhostsDirections) {};
	// Return pointOfTime
	int getPointOfTime() const { return pointOfTime; }
	// Return the key
	char getKey() const { return key; }
	// Return the wandering ghosts directions vector
	std::vector<int>& getGhostsVector() { return wanderingGhostsDirections; }
	// Change the pointOfTime
	void setPointOfTime(int _pointOfTim) { pointOfTime = _pointOfTim; }
	// Change the key
	void setKey(int _key) { key = _key; }
	// For the save mode ghosts vector
	void ghostsVectorResize(int size) { wanderingGhostsDirections.resize(size, 0); };
	// Read a steps segment from a file into a StepSegment obj
};

