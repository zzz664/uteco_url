#include "Time.h"

Time::Time()
{
	currentTime = 0.0f;
	deltaTime = 0.0f;

	QueryPerformanceCounter(&lInterval);
	QueryPerformanceFrequency(&frequency);
}

Time::~Time()
{

}

Time* Time::GetInstance()
{
	static Time Instance;
	return &Instance;
}

void Time::Update()
{
	QueryPerformanceCounter(&rInterval);
	__int64 Interval = (rInterval.QuadPart - lInterval.QuadPart);

	deltaTime = (double)Interval / (double)frequency.QuadPart;

	lInterval = rInterval;

	currentTime += deltaTime;
}
