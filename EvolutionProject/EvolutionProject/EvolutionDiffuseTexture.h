#ifndef _EVOLUTIONDIFFUSETEXTURE_H_
#define _EVOLUTIONDIFFUSETEXTURE_H_

#include "EvolutionShader.h"

class EVDiffuseTexture : public EVShader
{

private:

	D3DXCOLOR			ambientColor;
	LPDIRECT3DTEXTURE9	texture;

public:

	EVDiffuseTexture(LPDIRECT3DTEXTURE9 texture, D3DXCOLOR ambientColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	~EVDiffuseTexture();

	void Update();

public:

	void		Ambient(D3DXCOLOR ambientColor);
	D3DXCOLOR	Ambient() { return ambientColor; }

	void		Texture(LPDIRECT3DTEXTURE9 texture);
};

#endif