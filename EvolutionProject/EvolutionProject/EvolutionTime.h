#ifndef _EVOLUTIONTIME_H_
#define _EVOLUTIONTIME_H_

#include <Windows.h>

#define EVTime EvolutionTime::GetInstance()

class EvolutionTime 
{

private:

	LARGE_INTEGER	lInterval;
	LARGE_INTEGER	rInterval;
	LARGE_INTEGER	frequency;

	float			deltaTime;
	float			currentTime;

	DWORD			fps;

private:

	EvolutionTime();

	void CalcFPS();

public:

	~EvolutionTime();

	static EvolutionTime* GetInstance();

	//************************************<Description>***********************************************
	//	deltaTime과 currentTime을 매 프레임마다 업데이트 해주는 함수이다.
	void Update();

public:

	//************************************<Description>***********************************************
	//	프레임과 프레임사이의 시간을 반환하는 함수이다.
	float DeltaTime()	{ return deltaTime; }

	//************************************<Description>***********************************************
	//	응용프로그램이 실행되고나서부터 지난 시간을 반환하는 함수이다.
	float CurrentTime() { return currentTime; }

	//************************************<Description>***********************************************
	//	응용프로그램의 초당 프레임수를 반환하는 함수이다.
	DWORD FPS()			{ return fps; }

};

#endif