#pragma once

#include <fstream>
#include <vector>
#include <string>

enum class OpenMode {WRITE, READ};

struct FileSuffix {
	constexpr static const char* SCREEN = "screen.txt";
	constexpr static const char* STEPS = "steps.txt";
	constexpr static const char* RESULT = "result.txt";
};

// Search the names of the relevant files in pwd and add them to a vector
void getRelevantFiles(std::vector<std::string>& fileNames, const char* suffix);
// Prints a message to the screen after encountering a file related error
// If the inGame is true - the files are handled in a running game, therefore exiting to main menu
void printErrorFileRelatedMessage(bool inGame, const char* errorMessage);
// Set the file position to the beginning
void returnToFileBeginning(std::fstream& file);
// Open the file specified in fileName into file ifstream
void openFile(std::fstream& file,const std::string& fileName, OpenMode mode);