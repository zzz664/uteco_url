#include "EvolutionDiffuseSkinning.h"
#include "EvolutionEffectManager.h"
#include "EvolutionCore.h"

EVDiffuseSkinning::EVDiffuseSkinning(LPDIRECT3DTEXTURE9 texture, D3DXCOLOR ambientColor)
{
	this->ambientColor = ambientColor;
	this->texture = texture;

	_path = "Assets/Shader/DiffuseSkinningTexture.shader";

	EVEffectManager->Add(_path, NULL);

	_shader = EVEffectManager->Get(_path)->pEffect;

	_shader->SetVector("lightPosition", &D3DXVECTOR4(EVSystem->GlobalLightPosition(), 1));
	_shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
	_shader->SetTexture("defaultMap", texture);
}

EVDiffuseSkinning::~EVDiffuseSkinning()
{

}

void EVDiffuseSkinning::Update()
{
	_shader->SetVector("lightPosition", &D3DXVECTOR4(EVSystem->GlobalLightPosition(), 1));
}

void EVDiffuseSkinning::Ambient(D3DXCOLOR ambient)
{
	ambientColor = ambient;

	_shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
}

void EVDiffuseSkinning::Texture(LPDIRECT3DTEXTURE9 texture)
{
	this->texture = texture;

	_shader->SetTexture("defaultMap", texture);
}