#include <windows.h>
#include "InputManager.h"

InputManager::InputManager()
{
	for (int i = 0; i < 256; ++i)
	{
		oldKeyState[i] = currentKeyState[i] = false;
	}
}

InputManager::~InputManager()
{

}

InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}

void InputManager::Update()
{
	for (int i = 0; i < 256; ++i)
	{
		oldKeyState[i] = currentKeyState[i];
		currentKeyState[i] = GetKeyState(i) & 0x8000;
	}
}

bool InputManager::GetKey(unsigned int key)
{
	if (oldKeyState[key] == true && currentKeyState[key] == true)
	{
		return true;
	}

	return false;
}

bool InputManager::GetKeyDown(unsigned int key)
{
	if (oldKeyState[key] == false && currentKeyState[key] == true)
	{
		return true;
	}

	return false;
}

bool InputManager::GetKeyUp(unsigned int key)
{
	if (oldKeyState[key] == true && currentKeyState[key] == false)
	{
		return true;
	}

	return false;
}

void InputManager::UpdateMousePosition(int x, int y)
{
	screenMouseX = x;
	screenMouseY = y;
}

void InputManager::GetMousePosition(int& x, int& y)
{
	x = screenMouseX;
	y = screenMouseY;
}