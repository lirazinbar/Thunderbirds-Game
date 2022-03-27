#pragma once

class Game {
	static int livesCount;
	static bool keepPlaying;
public:
	void run();
	void play();
	static int getLivesCount() { return livesCount; }
	static void decreseLives() { Game::livesCount -= 1; }
	static void stopPlaying() { Game::keepPlaying = false; }
	bool isGameLost();
};