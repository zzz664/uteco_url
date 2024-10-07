#ifndef _EVOLUTIONINPUT_H_
#define _EVOLUTIONINPUT_H_

#include <Windows.h>
#include <string>

#define EVInput EvolutionInput::GetInstance()

class EvolutionInput 
{

private:

	int _oldMouseX;
	int _oldMouseY;

	int _currentMouseX;
	int _currentMouseY;

	float _horizontal;
	float _vertical;

	bool _oldKeyState[256];
	bool _currentKeyState[256];

	bool _mouseMove;

private:

	EvolutionInput();

	void UpdateHorizontal();
	void UpdateVertical();

public:

	~EvolutionInput();

	static EvolutionInput* GetInstance();

	//************************************<Description>***********************************************
	//	�� �Լ��� �� �����Ӹ��� ȣ��Ǹ� Ű���¸� ������Ʈ���ִ� �Լ��̴�.
	void Update();

public:

	//************************************<Description>***********************************************
	//	�� �Լ��� Ű���峪 ���콺�� ���ȴ��� üũ�ϴ� �Լ��̴�.
	//	���ڷ� ���� Ű�ڵ忡 �ش��ϴ� Ű�� ��� �������� ���� true�� ��ȯ�ϰ�
	//	�� ���� ��쿡�� false�� ��ȯ�Ѵ�.
	bool GetKey(unsigned int keyCode);

	//************************************<Description>***********************************************
	//	�� �Լ��� Ű���峪 ���콺�� ���ȴ��� üũ�ϴ� �Լ��̴�.
	//	���ڷ� ���� Ű�ڵ忡 �ش��ϴ� Ű�� ������ ���� true�� ��ȯ�ϰ�
	//	�� ���� ��쿡�� false�� ��ȯ�Ѵ�.
	bool GetKeyDown(unsigned int keyCode);

	//************************************<Description>***********************************************
	//	�� �Լ��� Ű���峪 ���콺�� ���ȴ��� üũ�ϴ� �Լ��̴�.
	//	���ڷ� ���� Ű�ڵ忡 �ش��ϴ� Ű�� ���ȴ� ���������� true�� ��ȯ�ϰ�
	//	�� ���� ��쿡�� false�� ��ȯ�Ѵ�.
	bool GetKeyUp(unsigned int keyCode);

	//************************************<Description>***********************************************
	//	�� �Լ��� ������ ���̽�ƽ�� ������� �������� ��ȭ���� ��ȯ�ϴ� �Լ��̴�.
	//	���ڷ� �����ִ� axis���� "Horizontal", "Vertical" �ΰ��̴�. (��ҹ��� ����� �������)
	//	Horizontal�� �ְԵǸ� Ű���� ��, ��, A, D�� �������� ��ȭ���� ��ȯ�Ѵ�.
	//	Ű���� ��, A�� ������ 0 ~ -1 ���̰��� ��ȯ�Ѵ�
	//	Ű���� ��, D�� ������ 0 ~ 1 ���̰��� ��ȯ�Ѵ�
	//	Vertical�� �ְԵǸ� Ű���� ��, ��, W, S�� �������� ��ȭ���� ��ȯ�Ѵ�.
	//	Ű���� ��, W�� ������ 0 ~ 1 ���̰��� ��ȯ�Ѵ�
	//	Ű���� ��, S�� ������ 0 ~ -1 ���̰��� ��ȯ�Ѵ�
	float GetAxis(std::string axis);

public:

	//************************************<Description>***********************************************
	//	�� �Լ��� ���콺�� X��ǥ�� ��ȯ�ϴ� �Լ��̴�.
	int MousePositionX()	{ return _currentMouseX; }

	//************************************<Description>***********************************************
	//	�� �Լ��� ���콺�� Y��ǥ�� ��ȯ�ϴ� �Լ��̴�.
	int MousePositionY()	{ return _currentMouseY; }

	bool MouseMove()		{ return _mouseMove; }

public:

	void MouseMove(bool mouseMove) { _mouseMove = mouseMove; }

};

#endif