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
	//	이 함수는 매 프레임마다 호출되며 키상태를 업데이트해주는 함수이다.
	void Update();

public:

	//************************************<Description>***********************************************
	//	이 함수는 키보드나 마우스가 눌렸는지 체크하는 함수이다.
	//	인자로 들어온 키코드에 해당하는 키가 계속 눌려있을 때만 true를 반환하고
	//	그 외의 경우에는 false를 반환한다.
	bool GetKey(unsigned int keyCode);

	//************************************<Description>***********************************************
	//	이 함수는 키보드나 마우스가 눌렸는지 체크하는 함수이다.
	//	인자로 들어온 키코드에 해당하는 키가 눌렸을 때만 true를 반환하고
	//	그 외의 경우에는 false를 반환한다.
	bool GetKeyDown(unsigned int keyCode);

	//************************************<Description>***********************************************
	//	이 함수는 키보드나 마우스가 눌렸는지 체크하는 함수이다.
	//	인자로 들어온 키코드에 해당하는 키가 눌렸다 때졌을때만 true를 반환하고
	//	그 외의 경우에는 false를 반환한다.
	bool GetKeyUp(unsigned int keyCode);

	//************************************<Description>***********************************************
	//	이 함수는 가상의 조이스틱의 가로축과 세로축의 변화량을 반환하는 함수이다.
	//	인자로 쓸수있는 axis값은 "Horizontal", "Vertical" 두개이다. (대소문자 제대로 적어야함)
	//	Horizontal을 넣게되면 키보드 좌, 우, A, D가 눌렸을때 변화량을 반환한다.
	//	키보드 좌, A가 눌리면 0 ~ -1 사이값을 반환한다
	//	키보드 우, D가 눌리면 0 ~ 1 사이값을 반환한다
	//	Vertical을 넣게되면 키보드 상, 하, W, S가 눌렸을때 변화량을 반환한다.
	//	키보드 상, W가 눌리면 0 ~ 1 사이값을 반환한다
	//	키보드 하, S가 눌리면 0 ~ -1 사이값을 반환한다
	float GetAxis(std::string axis);

public:

	//************************************<Description>***********************************************
	//	이 함수는 마우스의 X좌표를 반환하는 함수이다.
	int MousePositionX()	{ return _currentMouseX; }

	//************************************<Description>***********************************************
	//	이 함수는 마우스의 Y좌표를 반환하는 함수이다.
	int MousePositionY()	{ return _currentMouseY; }

	bool MouseMove()		{ return _mouseMove; }

public:

	void MouseMove(bool mouseMove) { _mouseMove = mouseMove; }

};

#endif