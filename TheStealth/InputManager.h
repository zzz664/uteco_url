#ifndef _INPUTMANAGER_H_
#define _INPUTMANAGER_H_

#define INPUT InputManager::GetInstance()

class InputManager
{
private:

	int screenMouseX;
	int screenMouseY;

	bool oldKeyState[256];
	bool currentKeyState[256];

private:

	InputManager();

public:

	~InputManager();

	static InputManager* GetInstance();

public:

	void Update();
	void UpdateMousePosition(int x, int y);

	bool GetKey(unsigned int key);
	bool GetKeyDown(unsigned int key);
	bool GetKeyUp(unsigned int key);

	void GetMousePosition(int& x, int& y);
};

#endif