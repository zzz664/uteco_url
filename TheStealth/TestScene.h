#ifndef _TESTSCENE_H_
#define _TESTSCENE_H_

#include "Scene.h"
#include "Camera.h"
#include "Sprite.h"
#include "Skybox.h"
#include "Water.h"
#include "MyJet.h"
#include "Missile.h"

class TestScene : public Scene
{
	Camera* camera;
	Skybox*	skybox;

	Water* water;

	MyJet* jet;
	Jet* testJet;

	Missile* missile;

	ImageAnimation* testExplode;

public:

	TestScene();
	~TestScene();

	void Update(float eTime);
	void Render();
};

#endif