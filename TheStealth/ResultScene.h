#ifndef _RESULTSCENE_H_
#define _RESULTSCENE_H_

#include "Scene.h"
#include "Sprite.h"
#include "Font.h"
#include "ResultInfo.h"

class ResultScene : public Scene
{

private:

	Font* font;
	Font* font2;

	Sprite* background[6];

	ResultInfo* info[2];

	float ratioX;
	float ratioY;

public:
	
	ResultScene();
	~ResultScene();

	void Update(float eTime);
	void Render();

};

#endif