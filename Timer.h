#pragma once

#include <chrono>

class Timer {
	// int tickStartTime;  //The start time for each "tick"
	// std::chrono::duration<float, std::milli> deltaTime{ 0 }; // In miliseconds
	int timeLeft = 0; // Countdown
public:
	// Reset the "tick" start time to now
	// void resetTickStartTime() { tickStartTime = 120 }
	// Return the delta time
	// float getDeltaTime() const { return deltaTime.count(); };
	// Advance the timer's delta time
	void tick() { timeLeft -= 1; }
	// Return the time left to screen
	int getTimeLeft() const { return timeLeft; }
	// Set the time of the screen accdording to the header in the screen file
	void setTimeLeft(int _timeLeft) { timeLeft = _timeLeft; }
	// Reduce time left by 1
	void reduceTimeLeft() { timeLeft -= 1; }
};