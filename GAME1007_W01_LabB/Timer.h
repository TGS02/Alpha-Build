#pragma once
#include <SDL_ttf.h>
class Timer
{
private:
	int startTicks; // The time when timer started.
	int pausedTicks; // The time stored when timer was paused.
	bool started;
	bool paused;
public:
	Timer();
	void start();
	void pause();
	void unpause();
	void stop();
	int get_ticks(); // returns the time.
	bool is_started();
	bool is_paused();

};

