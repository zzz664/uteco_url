#include "DiffuseShader.h"
#include "DirectX9.h"

DiffuseShader::DiffuseShader(LPDIRECT3DTEXTURE9 texture, D3DXCOLOR ambientColor)
{
	this->ambientColor = ambientColor;
	this->texture = texture;

	path = "Shader/diffuse.fx";

	D3DXCreateEffectFromFileA(DirectX9->GetDevice(), path.c_str(), NULL, NULL, 0, NULL, &shader, NULL);

	shader->SetVector("lightPosition", &D3DXVECTOR4(DirectX9->GetLightPosition(), 1));
	shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
	shader->SetTexture("defaultMap", texture);
}

DiffuseShader::~DiffuseShader()
{

}

void DiffuseShader::Update()
{
	shader->SetTexture("defaultMap", texture);
	shader->SetVector("lightPosition", &D3DXVECTOR4(DirectX9->GetLightPosition(), 1));
}

void DiffuseShader::SetAmbient(D3DXCOLOR ambient)
{
	ambientColor = ambient;

	shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
}

void DiffuseShader::SetTexture(LPDIRECT3DTEXTURE9 texture)
{
	this->texture = texture;

	shader->SetTexture("defaultMap", texture);
}