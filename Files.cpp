#include "Files.h"
#include "Utils.h"
#include "Game.h"
#include <filesystem>
#include <Windows.h>
#include <conio.h>

void getRelevantFiles(std::vector<std::string>& fileNames, const char* suffix) {
	std::filesystem::path pwd = std::filesystem::current_path();
	std::string currentFileName;

	for (auto& file : std::filesystem::directory_iterator(pwd)) {
		currentFileName = file.path().filename().string();
		// Search for all the tb*.screen files in pwd
		if (file.is_regular_file() && currentFileName.starts_with("tb") && currentFileName.ends_with(suffix)) {
			fileNames.push_back(currentFileName);
		}
	}
	if (Game::getMainGameMode() != GameMode::SAVE) {
		// If there are no screen files
		if (fileNames.size() == 0) {
			printErrorFileRelatedMessage(false, "Error! The files you are searching for are not in the directory. Exiting to main menu...");
		}
		else {
			// Sort the file names in lexicographical order
			std::sort(fileNames.begin(), fileNames.end());
		}
	}
}

void printErrorFileRelatedMessage(bool inGame, const char* errorMessage) {
	clrscr();
	gotoxy(int(PrintPoints::MESSAGE_X), int(PrintPoints::MESSAGE_Y));
	std::cout << errorMessage << std::endl;
	if (inGame) {
		Game::stopPlaying();
		// Sleep for 3 seconds
		Sleep(3000);
	}
}

void returnToFileBeginning(std::fstream& file) {
	file.clear();
	file.seekg(0);
}

void openFile(std::fstream& file, const std::string& fileName, OpenMode mode) {
	if (mode == OpenMode::READ)
		file.open(fileName, std::ios::in);
	else
		file.open(fileName, std::ios::out);
	// If there is a problem opening the file
	if (file.fail()) {
		clrscr();
		printErrorFileRelatedMessage(true, "Error! There was a problem opening the file.");
		Game::stopPlaying();
	}
}