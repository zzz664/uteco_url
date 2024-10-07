#ifndef _SKYBOX_H_
#define _SKYBOX_H_

#include "DxObject.h"

class Camera;

class Skybox : public DxObject
{
public:

	struct SKYBOXVERTEX
	{
		float x, y, z;
		float u, v;
	};

private:

	LPDIRECT3DDEVICE9		device;

	LPDIRECT3DTEXTURE9		textures[6];
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	Camera*					camera;

	void BuildVertex(SKYBOXVERTEX* vertex, float x, float y, float z, float u, float v);

public:

	Skybox(Camera* camera);
	~Skybox();

	void Create();

	void Update(float eTime);
	void Render();
};

#endif