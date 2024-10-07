#ifndef _TIME_H_
#define _TIME_H_

#include <windows.h>

#define TIME Time::GetInstance()

class Time
{
private:

	LARGE_INTEGER	lInterval;
	LARGE_INTEGER	rInterval;
	LARGE_INTEGER	frequency;

	float			deltaTime;
	float			currentTime;

	Time();

public:

	~Time();

	static Time* GetInstance();

	void Update();

public:

	float DeltaTime()	{ return deltaTime; }
	float CurrentTime() { return currentTime; }
};

#endif