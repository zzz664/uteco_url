#ifndef _HPFORM_H_
#define _HPFORM_H_

#include "Sprite.h"
#include "Font.h"

class HPForm : public DxObject2D
{

private:

	Sprite* hpForm;
	Sprite*	hp[5];

	Font*	font;

	float healthPoint;
	float hpValue[5];

	int	  currentIndex;
	
	float ratioX;
	float ratioY;

public:

	HPForm();
	~HPForm();

	void SetHP(float hp);
	float GetHP() { return healthPoint; }

	void Update(float eTime);
	void Render();
};

#endif