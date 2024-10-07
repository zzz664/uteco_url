#include "Sprite.h"
#include "DirectX9.h"
#include "TextureManager.h"

Sprite::Sprite(std::string path)
{
	device = DirectX9->GetDevice();
	sprite = DirectX9->GetSprite();
	texture = TEXTURE->LoadTextureFromFile(path);

	D3DSURFACE_DESC desc;
	texture->GetLevelDesc(0, &desc);

	width = desc.Width;
	height = desc.Height;

	rect.left = 0;
	rect.top = 0;
	rect.right = width;
	rect.bottom = height;

	alphaBlend = false;

	color = D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f);

	SetScale(GetScale().x * DirectX9->GetRatioX(), GetScale().y * DirectX9->GetRatioY());

	relativeRect.left = 0;
	relativeRect.top = 0;
	relativeRect.right = width * DirectX9->GetRatioX();
	relativeRect.bottom = height * DirectX9->GetRatioY();

	relativeWidth = relativeRect.right;
	relativeHeight = relativeRect.bottom;
}

Sprite::~Sprite()
{
	
}

void Sprite::Update(float eTime)
{

}

void Sprite::Render()
{
	DxObject2D::Render();

	sprite->SetTransform(&worldMatrix);
	sprite->Begin(D3DXSPRITE_ALPHABLEND);

	if (alphaBlend)
	{
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	}

	sprite->Draw(texture, &rect, NULL, NULL, color);
	sprite->End();
}