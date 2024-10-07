#ifndef _LISTENER_H_
#define _LISTENER_H_

#include <fmod.hpp>
#include <D3DX10math.h>

class Listener
{

private:

	FMOD_VECTOR last;
	FMOD_VECTOR position;

	FMOD_VECTOR forward;
	FMOD_VECTOR up;
	FMOD_VECTOR vel;

public:

	Listener();
	~Listener();

	void Update(float eTime);

public:

	void SetPosition(float x, float y, float z);
	void SetForward(float x, float y, float z);
	void SetUp(float x, float y, float z);

	void SetPosition(D3DXVECTOR3 position);
	void SetForward(D3DXVECTOR3 forward);
	void SetUp(D3DXVECTOR3 up);
};

#endif