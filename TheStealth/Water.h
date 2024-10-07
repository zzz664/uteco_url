#ifndef _WATER_H_
#define _WATER_H_

#include "DxObject.h"
#include "WaterShader.h"

class Camera;

class Water : public DxObject
{
	
public:

	struct WATER_VERTEX
	{
		float x, y, z;
		float u, v;
	};

private:

	Camera*					camera;
	
	LPDIRECT3DDEVICE9		device;
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	float					waterSize;
	float					textureScale;
	float					normalScale;
	float					normalSpeedX;
	float					normalSpeedY;

	float					waterFreq;
	float					waterAmp;

	float					reflectionAmount;
	float					waterAmount;

	float					hdrMultiplier;

	WaterShader*			waterShader;

public:

	Water(Camera* camera, float waterSize);
	~Water();

	void Update(float eTime);
	void Render();

	void SetWaterFreq(float freq);
	void SetWaterAmp(float amp);
	void SetTextureScale(float scale);
	void SetNormalScale(float scale);
	void SetNormalSpeed(float speedX, float speedY);
	void SetReflectionAmount(float amount);
	void SetWaterAmount(float amount);
	void SetHDRMultiplier(float multiplier);

};

#endif