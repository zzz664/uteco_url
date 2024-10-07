#ifndef _IMAGEANIMATION_H_
#define _IMAGEANIMATION_H_

#include "Image.h"
#include <string>

class Camera;

using namespace std;

class ImageAnimation : public DxObject
{

private:

	int maxFrame;

	float currentFrame;

	float frameSpeed;

	Camera* camera;

	Image** frame;

	bool isProceed;

public:

	ImageAnimation(Camera* camera, string path, int numImage, float frameSpeed = 1.0f);
	~ImageAnimation();

	void SetBillboardState(BILLBOARD_STATE state);
	void SetAlphaBlend(bool alphaBlend);

	void SetProceed(bool isProceed) { this->isProceed = isProceed; }
	bool GetProceed() { return isProceed; }

	void Update(float eTime);
	void Render();


	bool isComplete;
};

#endif