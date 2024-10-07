#include "EvolutionInput.h"
#include "EvolutionTime.h"
#include "EvolutionCore.h"

EvolutionInput::EvolutionInput()
{
	_horizontal = 0;
	_vertical = 0;

	_oldMouseX = _oldMouseY = 0;
	_currentMouseX = _currentMouseY = 0;

	for (int i = 0; i < 256; ++i)
	{
		_oldKeyState[i] = _currentKeyState[i] = false;
	}

	_mouseMove = false;
}

EvolutionInput::~EvolutionInput()
{

}

EvolutionInput* EvolutionInput::GetInstance()
{
	static EvolutionInput instance;
	return &instance;
}

void EvolutionInput::Update()
{
	for (int i = 0; i < 256; ++i)
	{
		_oldKeyState[i] = _currentKeyState[i];
		_currentKeyState[i] = GetKeyState(i) & 0x8000;
	}

	UpdateHorizontal();
	UpdateVertical();

	_oldMouseX = _currentMouseX;
	_oldMouseY = _currentMouseY;

	POINT pt;
	GetCursorPos(&pt);

	_currentMouseX = pt.x;
	_currentMouseY = pt.y;

}

void EvolutionInput::UpdateHorizontal()
{
	if (_currentKeyState[VK_LEFT] == true || _currentKeyState['A'] == true)
	{
		_horizontal -= 2 * EVTime->DeltaTime();
		if (_horizontal <= -1.0f)
		{
			_horizontal = -1.0f;
		}
	}

	if (_currentKeyState[VK_RIGHT] == true || _currentKeyState['D'] == true)
	{
		_horizontal += 2 * EVTime->DeltaTime();
		if (_horizontal >= 1.0f)
		{
			_horizontal = 1.0f;
		}
	}

	if (_currentKeyState[VK_LEFT] == false && _currentKeyState[VK_RIGHT] == false &&
		_currentKeyState['A'] == false && _currentKeyState['D'] == false)
	{
		if (_horizontal >= 0.0f)
		{
			_horizontal -= 2 * EVTime->DeltaTime();
			if (_horizontal <= 0.0f)
			{
				_horizontal = 0.0f;
			}
		}
		else if (_horizontal <= 0.0f)
		{
			_horizontal += 2 * EVTime->DeltaTime();
			if (_horizontal >= 0.0f)
			{
				_horizontal = 0.0f;
			}
		}
	}
}

void EvolutionInput::UpdateVertical()
{
	if (_currentKeyState[VK_UP] == true || _currentKeyState['W'] == true)
	{
		_vertical += 2 * EVTime->DeltaTime();
		if (_vertical >= 1.0f)
		{
			_vertical = 1.0f;
		}
	}

	if (_currentKeyState[VK_DOWN] == true || _currentKeyState['S'] == true)
	{
		_vertical -= 2 * EVTime->DeltaTime();
		if (_vertical <= -1.0f)
		{
			_vertical = -1.0f;
		}
	}

	if (_currentKeyState[VK_DOWN] == false && _currentKeyState[VK_UP] == false &&
		_currentKeyState['W'] == false && _currentKeyState['S'] == false)
	{
		if (_vertical >= 0.0f)
		{
			_vertical -= 2 * EVTime->DeltaTime();
			if (_vertical <= 0.0f)
			{
				_vertical = 0.0f;
			}
		}
		else if (_vertical <= 0.0f)
		{
			_vertical += 2 * EVTime->DeltaTime();
			if (_vertical >= 0.0f)
			{
				_vertical = 0.0f;
			}
		}
	}
}

bool EvolutionInput::GetKey(unsigned int keyCode)
{
	if (_oldKeyState[keyCode] == true && _currentKeyState[keyCode] == true)
	{
		return true;
	}

	return false;
}

bool EvolutionInput::GetKeyDown(unsigned int keyCode)
{
	if (_oldKeyState[keyCode] == false && _currentKeyState[keyCode] == true)
	{
		return true;
	}

	return false;
}

bool EvolutionInput::GetKeyUp(unsigned int keyCode)
{
	if (_oldKeyState[keyCode] == true && _currentKeyState[keyCode] == false)
	{
		return true;
	}

	return false;
}

float EvolutionInput::GetAxis(std::string axis)
{
	if (axis == "Horizontal")
	{
		return _horizontal;
	}

	if (axis == "Vertical")
	{
		return _vertical;
	}

	if (axis == "Mouse X")
	{
		return (_oldMouseX - _currentMouseX);
	}

	if (axis == "Mouse Y")
	{
		return (_oldMouseY - _currentMouseY);
	}

	return 0.0f;
}