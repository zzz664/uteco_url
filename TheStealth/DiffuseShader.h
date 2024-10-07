#ifndef _DIFFUSESHADER_H_
#define _DIFFUSESHADER_H_

#include "Shader.h"

class DiffuseShader : public Shader
{
private:

	D3DXCOLOR			ambientColor;
	LPDIRECT3DTEXTURE9	texture;

public:

	DiffuseShader(LPDIRECT3DTEXTURE9 texture, D3DXCOLOR ambientColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	~DiffuseShader();

	void Update();

public:

	void		SetAmbient(D3DXCOLOR ambientColor);
	D3DXCOLOR	GetAmbient() { return ambientColor; }

	void		SetTexture(LPDIRECT3DTEXTURE9 texture);

};

#endif