#pragma once

#include <chrono>

enum class Time { GAME_TIME = 120 };  // 120 seconds

class Timer {
	std::chrono::steady_clock::time_point tickStartTime;  //The start time for each "tick"
	std::chrono::duration<float, std::milli> deltaTime{ 0 }; // In miliseconds
	int timeLeft = int(Time::GAME_TIME); // Countdown
public:
	// Reset the timer to the initial state
	void resetTimer() { timeLeft = int(Time::GAME_TIME); resetTickStartTime(); }
	// Reset the "tick" start time to now
	void resetTickStartTime() { tickStartTime = std::chrono::steady_clock::now(); }
	// Return the delta time
	float getDeltaTime() const { return deltaTime.count(); };
	// Advance the timer's delta time
	void tick() { deltaTime = std::chrono::steady_clock::now() - tickStartTime; }
	// Return the time left to screen
	int getTimeLeft() const { return timeLeft; }
	// Reduce time left by 1
	void reduceTimeLeft() { timeLeft -= 1; }
};