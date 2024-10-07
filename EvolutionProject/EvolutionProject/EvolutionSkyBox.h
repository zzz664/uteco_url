#ifndef _EVOLUTIONSKYBOX_H_
#define _EVOLUTIONSKYBOX_H_

#include "EvolutionGameObject.h"

struct SKYBOXVERTEX 
{
	float x, y, z;
	float u, v;
};

class EVSkyBox : public EVGameObject 
{

private:

	LPDIRECT3DTEXTURE9		textures[6];
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

private:

	void BuildVertex(SKYBOXVERTEX* vertex, float x, float y, float z, float u, float v);

public:

	EVSkyBox();
	~EVSkyBox();

	void Create();

	void Update();
	void Render();

};

#endif