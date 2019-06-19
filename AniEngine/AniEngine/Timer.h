#pragma once

#include "Exports.h"
#include <ctime>

static class ENGINEDLL_API Timer
{
private:
	static double deltaTime;
	static clock_t begin;
	static clock_t end;
public:
	Timer();
	~Timer();
	static double & GetDeltaTime();
	static void BeginClock();
	static void EndClock();
};

