#ifndef _EVOLUTIONUIFONT_H_
#define _EVOLUTIONUIFONT_H_

#include "EvolutionGameObject2D.h"

#include <string>

class EVUIFont : public EVGameObject2D
{

private:
	
	LPD3DXFONT	_font;
	D3DXCOLOR	_color;

	std::string _text;
	int			_size;

public:

	EVUIFont(int size = 10);
	~EVUIFont();

	void Update();
	void Render();

public:

	void Text(LPSTR fmt, ...);
	void Color(D3DXCOLOR color) { _color = color; }

};

#endif