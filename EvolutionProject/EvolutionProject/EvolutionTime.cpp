#include "EvolutionTime.h"
#include "EvolutionCore.h"

EvolutionTime::EvolutionTime() 
{
	currentTime = 0.0f;
	deltaTime = 0.0f;

	fps = 0;

	QueryPerformanceCounter(&lInterval);
	QueryPerformanceFrequency(&frequency);
}

EvolutionTime::~EvolutionTime()
{

}

void EvolutionTime::CalcFPS()
{
	static DWORD	nTick = 0;

	if (GetTickCount() - nTick > 1000)
	{
		nTick = GetTickCount();

		char title[100];

		sprintf(title, "%s - fps : %d", EVSystem->ApplicationName().c_str(), fps);

		SetWindowText(EVSystem->Hwnd(), title);

		fps = 0;
		return;
	}
	fps++;
}

EvolutionTime* EvolutionTime::GetInstance()
{
	static EvolutionTime Instance;
	return &Instance;
}

void EvolutionTime::Update() 
{
	QueryPerformanceCounter(&rInterval);
	__int64 Interval = (rInterval.QuadPart - lInterval.QuadPart);

	deltaTime = (double)Interval / (double)frequency.QuadPart;

	lInterval = rInterval;

	currentTime += deltaTime;

	CalcFPS();
}
