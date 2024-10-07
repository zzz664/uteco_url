#ifndef _MYJET_H_
#define _MYJET_H_

#include "Jet.h"

class MyJet : public Jet
{
public:
	MyJet(Camera* camera);
	~MyJet();

	void  Initialize(float basicSpeed, float minSpeed, float maxSpeed);

	void  Update(float eTime);
	void  Render();

	void  UpdatePosition(float eTime);

	void  SetBasicSpeed(float basicSpeed) { this->basicSpeed = basicSpeed; }
	float GetBasicSpeed() { return basicSpeed; }

	int slot;

	bool spawn = false;

private:

	void  UpdateMove(float eTime);
	void  UpdateSpeed(float eTime);

	float basicSpeed;
	float maxSpeed;
	float minSpeed;
	float pitch;
	bool  isEngineStart;

	float spawnTime;


};

#endif