#include "Timer.h"

double Timer::deltaTime;
clock_t Timer::begin;
clock_t Timer::end;

Timer::Timer()
{
}


Timer::~Timer()
{
}

void Timer::BeginClock()
{
	begin = clock();
}

void Timer::EndClock()
{
	end = clock();
	deltaTime = double(end - begin) / CLOCKS_PER_SEC;
}

double & Timer::GetDeltaTime()
{
	return deltaTime;
}