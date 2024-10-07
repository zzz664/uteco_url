#ifndef _TESTSCENE_H_
#define _TESTSCENE_H_

#include "EvolutionScene.h"
#include "EvolutionCamera.h"
#include "EvolutionSkyBox.h"
#include "EvolutionModel.h"
#include "EvolutionSprite2D.h"
#include "TestObject.h"

class TestScene : public EVScene
{

private:

	EVCamera* camera;
	EVSkyBox* skyBox;
	EVModel* model;
	EVSprite2D* sprite;
	TestObject* t1;
	TestObject* t2;
 
public:

	TestScene();
	~TestScene();

	void Update();
	void Render();
};

#endif