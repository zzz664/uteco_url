#include "EvolutionSprite2D.h"
#include "EvolutionCore.h"
#include "EvolutionTextureManager.h"

EVSprite2D::EVSprite2D(std::string path)
{
	_texture = EVTextureManager->LoadTextureFromFile(path);

	D3DSURFACE_DESC desc;
	_texture->GetLevelDesc(0, &desc);

	_width = desc.Width;
	_height = desc.Height;

	_drawAreaRect.left = 0;
	_drawAreaRect.top = 0;
	_drawAreaRect.right = _width;
	_drawAreaRect.bottom = _height;

	_useAlphaBlend = false;

	_color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);
}

EVSprite2D::~EVSprite2D()
{
	_texture->Release();
}

void EVSprite2D::Update()
{
	EVGameObject2D::Update();
}

void EVSprite2D::Render()
{
	EVGameObject2D::Render();

	EVSystem->DirectSprite()->SetTransform(&_transformMatrix);
	EVSystem->DirectSprite()->Begin(D3DXSPRITE_ALPHABLEND);

	if (_useAlphaBlend) 
	{
		EVSystem->DirectDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		EVSystem->DirectDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		EVSystem->DirectDevice()->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	}

	EVSystem->DirectSprite()->Draw(_texture, &_drawAreaRect, NULL, NULL, _color);
	EVSystem->DirectSprite()->End();
}