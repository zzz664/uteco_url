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
	//	deltaTime�� currentTime�� �� �����Ӹ��� ������Ʈ ���ִ� �Լ��̴�.
	void Update();

public:

	//************************************<Description>***********************************************
	//	�����Ӱ� �����ӻ����� �ð��� ��ȯ�ϴ� �Լ��̴�.
	float DeltaTime()	{ return deltaTime; }

	//************************************<Description>***********************************************
	//	�������α׷��� ����ǰ������� ���� �ð��� ��ȯ�ϴ� �Լ��̴�.
	float CurrentTime() { return currentTime; }

	//************************************<Description>***********************************************
	//	�������α׷��� �ʴ� �����Ӽ��� ��ȯ�ϴ� �Լ��̴�.
	DWORD FPS()			{ return fps; }

};

#endif