#ifndef _EVOLUTIONDIFFUSE_H_
#define _EVOLUTIONDIFFUSE_H_

#include "EvolutionShader.h"

class EVDiffuse : public EVShader
{

private:

	D3DXCOLOR	ambientColor;

public:

	EVDiffuse(D3DXCOLOR ambientColor = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	~EVDiffuse();

	void Update();

public:

	void		Ambient(D3DXCOLOR ambientColor);
	D3DXCOLOR	Ambient() { return ambientColor; }

};

#endif