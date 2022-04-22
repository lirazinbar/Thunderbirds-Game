#pragma once

#include <chrono>

class Timer {
	std::chrono::steady_clock::time_point tickStartTime;  //The start time for each "tick"
	std::chrono::duration<float, std::milli> deltaTime{ 0 }; // In miliseconds
	int timeLeft = 0; // Countdown
public:
	// Reset the "tick" start time to now
	void resetTickStartTime() { tickStartTime = std::chrono::steady_clock::now(); }
	// Return the delta time
	float getDeltaTime() const { return deltaTime.count(); };
	// Advance the timer's delta time
	void tick() { deltaTime = std::chrono::steady_clock::now() - tickStartTime; }
	// Return the time left to screen
	int getTimeLeft() const { return timeLeft; }
	// Set the time of the screen accdording to the header in the screen file
	void setTimeLeft(int _timeLeft) { timeLeft = _timeLeft; }
	// Reduce time left by 1
	void reduceTimeLeft() { timeLeft -= 1; }
};