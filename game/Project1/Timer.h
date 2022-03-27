#pragma once

#include <chrono>

enum class Time { GAME_TIME  = 120 };  // 120 seconds

class Timer {
	std::chrono::steady_clock::time_point tickStartTime;  //The start time for each "tick"
	std::chrono::duration<float, std::milli> deltaTime{ 0 }; // In miliseconds
	int timeLeft = int(Time::GAME_TIME); // Countdown
public:
	void resetTimer() { timeLeft = int(Time::GAME_TIME); resetTickStartTime(); }
	void resetTickStartTime() { tickStartTime = std::chrono::steady_clock::now(); }
	float getDeltaTime() { return deltaTime.count(); };
	void tick() { deltaTime = std::chrono::steady_clock::now() - tickStartTime; }
	int getTimeLeft() { return timeLeft; }
	void reduceTimeLeft() { timeLeft -= 1; }
};