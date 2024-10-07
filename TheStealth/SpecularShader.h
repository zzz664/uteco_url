#ifndef _SPECULARSHADER_H_
#define _SPECULARSHADER_H_

#include "Shader.h"

class Camera;

class SpecularShader : public Shader
{
private:

	Camera*				camera;

	D3DXCOLOR			ambientColor;
	LPDIRECT3DTEXTURE9	texture;

public:

	SpecularShader(Camera* camera, LPDIRECT3DTEXTURE9 texture, D3DXCOLOR ambientColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	~SpecularShader();

	void Update();

public:

	void		SetAmbient(D3DXCOLOR ambientColor);
	D3DXCOLOR	GetAmbient() { return ambientColor; }

	void		SetTexture(LPDIRECT3DTEXTURE9 texture);
};

#endif