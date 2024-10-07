#include "EvolutionDiffuse.h"
#include "EvolutionEffectManager.h"
#include "EvolutionCore.h"

EVDiffuse::EVDiffuse(D3DXCOLOR ambientColor)
{
	this->ambientColor = ambientColor;

	_path = "Assets/Shader/Diffuse.shader";

	EVEffectManager->Add(_path, NULL);

	_shader = EVEffectManager->Get(_path)->pEffect;

	_shader->SetVector("lightPosition", &D3DXVECTOR4(EVSystem->GlobalLightPosition(), 1));
	_shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
}

EVDiffuse::~EVDiffuse()
{

}

void EVDiffuse::Update()
{
	_shader->SetVector("lightPosition", &D3DXVECTOR4(EVSystem->GlobalLightPosition(), 1));
}

void EVDiffuse::Ambient(D3DXCOLOR ambient)
{
	ambientColor = ambient;

	_shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
}