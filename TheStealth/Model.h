#ifndef _MODEL_H_
#define _MODEL_H_

#include "DxObject.h"
#include "SpecularShader.h"
#include <string>

class Camera;

using namespace std;

class Model : public DxObject
{
private:

	LPD3DXMESH				mesh;
	D3DMATERIAL9*			meshMaterials;
	LPDIRECT3DTEXTURE9*		meshTextures;

	SpecularShader*			shader;

	DWORD					numMaterials;

public:

	Model(Camera* camera, string modelPath, string texturePath);
	~Model();

	void Update(float eTime);
	void Render();
};

#endif