#ifndef _TEXTURESHADER_H_
#define _TEXTURESHADER_H

#include "Shader.h"

class TextureShader : public Shader
{
private:

	D3DXCOLOR			ambientColor;
	LPDIRECT3DTEXTURE9	texture;

public:

	TextureShader(LPDIRECT3DTEXTURE9 texture, D3DXCOLOR ambientColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	~TextureShader();

	void Update();

public:

	void		SetAmbient(D3DXCOLOR ambientColor);
	D3DXCOLOR	GetAmbient() { return ambientColor; }

	void		SetTexture(LPDIRECT3DTEXTURE9 texture);
};

#endif