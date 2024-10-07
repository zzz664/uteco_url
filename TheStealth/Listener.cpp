#include "Listener.h"
#include "SoundManager.h"

Listener::Listener()
{

}

Listener::~Listener()
{

}

void Listener::Update(float eTime)
{
	vel.x = (position.x - last.x) * eTime * 1000;
	vel.y = (position.y - last.y) * eTime * 1000;
	vel.z = (position.z - last.z) * eTime * 1000;

	last = position;

	SOUND->GetSystem()->set3DListenerAttributes(0, &position, &vel, &forward, &up);
}

void Listener::SetPosition(float x, float y, float z)
{
	position.x = x;
	position.y = y;
	position.z = z;
}

void Listener::SetForward(float x, float y, float z)
{
	forward.x = x;
	forward.y = y;
	forward.z = z;
}

void Listener::SetUp(float x, float y, float z)
{
	up.x = x;
	up.y = y;
	up.z = z;
}

void Listener::SetPosition(D3DXVECTOR3 position)
{
	FMOD_VECTOR temp = { position.x, position.y, position.z };
	this->position = temp;
}

void Listener::SetForward(D3DXVECTOR3 forward)
{
	FMOD_VECTOR temp = { forward.x, forward.y, forward.z };
	this->forward = temp;
}

void Listener::SetUp(D3DXVECTOR3 up)
{
	FMOD_VECTOR temp = { up.x, up.y, up.z };
	this->up = temp;
}