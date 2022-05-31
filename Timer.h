#pragma once

#include <chrono>

class Timer {
	int timeLeft = 0; // Countdown
public:
	// Advance the timer
	void tick() { timeLeft -= 1; }
	// Return the time left to screen
	int getTimeLeft() const { return timeLeft; }
	// Set the time of the screen accdording to the header in the screen file
	void setTimeLeft(int _timeLeft) { timeLeft = _timeLeft; }
	// Reduce time left by 1
	void reduceTimeLeft() { timeLeft -= 1; }
};