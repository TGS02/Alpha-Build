#include "Timer.h"
#include  <SDL.h>
#include <iostream>
#include <sstream>

Timer::Timer()
{
	startTicks = 0;
	pausedTicks = 0;
	started = false;
	paused = false;
}

void Timer::start()
{
	started = true;
	paused = false;
	startTicks = SDL_GetTicks();
}

void Timer::pause()
{
	// Check if the timer has started, and has not been paused already.
	if ((started == true) && (paused == false))
	{
		paused = true;
		pausedTicks = SDL_GetTicks() - startTicks;
	}
}

void Timer::unpause()
{
	// Check if timer has been paused.
	if (paused == true)
	{
		paused = false;
		startTicks = SDL_GetTicks() - pausedTicks;
		pausedTicks = 0;
	}
}

void Timer::stop()
{
	started = false;
	paused = false;
}

int Timer::get_ticks()
{
	// Check if the timer is running.
	if (started == true)
	{
		// Check if timer is paused.
		if (paused == true)
		{
			return pausedTicks;
		}
		else
		{
			return SDL_GetTicks() - startTicks;
		}
	}
	// If the timer has not started
	// needed?!
	else
		return 0;
}

bool Timer::is_started()
{
	return started;
}

bool Timer::is_paused()
{
	return paused;
}

