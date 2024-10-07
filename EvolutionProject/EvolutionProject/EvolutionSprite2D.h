#ifndef _EVOLUTIONSPRITE2D_H_
#define _EVOLUTIONSPRITE2D_H_

#include "EvolutionGameObject2D.h"

class EVSprite2D : public EVGameObject2D 
{

private:

	LPDIRECT3DTEXTURE9	_texture;

	RECT				_drawAreaRect;
	D3DXCOLOR			_color;

	int					_width;
	int					_height;

	bool				_useAlphaBlend;

public:

	EVSprite2D(std::string path);
	~EVSprite2D();

	void Update();
	void Render();

public:

	RECT	Rect() { return _drawAreaRect; }

	int		Width() { return _width; }
	int		Height() { return _height; }

	D3DXCOLOR Color() { return _color; }

public:

	void	AlphaBlending(bool isUse) { _useAlphaBlend = isUse; }

	void	Rect(RECT rect) { _drawAreaRect = rect; }

	void	Color(D3DXCOLOR color) { _color = color; }

};

#endif