#include "ImageAnimation.h"

ImageAnimation::ImageAnimation(Camera* camera, string path, int numImage, float frameSpeed)
{
	this->camera = camera;

	maxFrame = numImage;

	this->frameSpeed = frameSpeed;
	
	currentFrame = 0.0f;

	frame = new Image*[maxFrame];

	char tmp[5];

	for (int i = 0; i < maxFrame; ++i)
	{
		frame[i] = new Image(camera, path + itoa(i, tmp, 10) + ".png");
		AddChild(frame[i]);
	}

	isProceed = false;
	isComplete = false;
}

ImageAnimation::~ImageAnimation()
{
	delete[] frame;
}

void ImageAnimation::Update(float eTime)
{
	DxObject::Update(eTime);

	if (isProceed)
	{
		currentFrame += frameSpeed * eTime;

		if (currentFrame >= maxFrame)
		{
			isComplete = true;
			currentFrame = 0.0f;
		}
	}
}

void ImageAnimation::Render()
{
	DxObject::Render();
	frame[(int)currentFrame]->Render();
}

void ImageAnimation::SetBillboardState(BILLBOARD_STATE state)
{
	for (int i = 0; i < maxFrame; ++i) frame[i]->SetBillboardState(state);
}

void ImageAnimation::SetAlphaBlend(bool alphaBlend)
{
	for (int i = 0; i < maxFrame; ++i) frame[i]->SetAlphaBlend(alphaBlend);
}