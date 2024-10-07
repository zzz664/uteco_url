#ifndef _WATERSHADER_H_
#define _WATERSHADER_H_

#include "Shader.h"

class Camera;

class WaterShader : public Shader
{

private:

	Camera* camera;

public:

	WaterShader(Camera* camera);
	~WaterShader();

	void Update(float eTime);
};

#endif