#include "TextureShader.h"
#include "DirectX9.h"

TextureShader::TextureShader(LPDIRECT3DTEXTURE9 texture, D3DXCOLOR ambientColor)
{
	this->ambientColor = ambientColor;
	this->texture = texture;

	path = "Shader/texture.fx";

	D3DXCreateEffectFromFileA(DirectX9->GetDevice(), path.c_str(), NULL, NULL, 0, NULL, &shader, NULL);

	shader->SetVector("color", &D3DXVECTOR4(ambientColor));
	shader->SetTexture("tex", texture);
}

TextureShader::~TextureShader()
{

}

void TextureShader::Update()
{
	shader->SetTexture("tex", texture);
}

void TextureShader::SetAmbient(D3DXCOLOR ambient)
{
	ambientColor = ambient;

	shader->SetVector("color", &D3DXVECTOR4(ambientColor));
}

void TextureShader::SetTexture(LPDIRECT3DTEXTURE9 texture)
{
	this->texture = texture;

	shader->SetTexture("tex", texture);
}