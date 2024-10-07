#include "EvolutionDiffuseTexture.h"
#include "EvolutionEffectManager.h"
#include "EvolutionCore.h"

EVDiffuseTexture::EVDiffuseTexture(LPDIRECT3DTEXTURE9 texture, D3DXCOLOR ambientColor)
{
	this->ambientColor = ambientColor;
	this->texture = texture;

	_path = "Assets/Shader/DiffuseTexture.shader";

	EVEffectManager->Add(_path, NULL);

	_shader = EVEffectManager->Get(_path)->pEffect;

	_shader->SetVector("lightPosition", &D3DXVECTOR4(EVSystem->GlobalLightPosition(), 1));
	_shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
	_shader->SetTexture("defaultMap", texture);
}

EVDiffuseTexture::~EVDiffuseTexture()
{

}

void EVDiffuseTexture::Update()
{
	_shader->SetVector("lightPosition", &D3DXVECTOR4(EVSystem->GlobalLightPosition(), 1));
}

void EVDiffuseTexture::Ambient(D3DXCOLOR ambient)
{
	ambientColor = ambient;

	_shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
}

void EVDiffuseTexture::Texture(LPDIRECT3DTEXTURE9 texture)
{
	this->texture = texture;

	_shader->SetTexture("defaultMap", texture);
}