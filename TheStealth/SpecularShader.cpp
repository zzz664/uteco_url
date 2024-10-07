#include "SpecularShader.h"
#include "EffectManager.h"
#include "DirectX9.h"
#include "Camera.h"

SpecularShader::SpecularShader(Camera* camera, LPDIRECT3DTEXTURE9 texture, D3DXCOLOR ambientColor)
{
	this->camera = camera;

	this->ambientColor = ambientColor;
	this->texture = texture;

	path = "Shader/specular.fx";

	D3DXCreateEffectFromFileA(DirectX9->GetDevice(), path.c_str(), NULL, NULL, 0, NULL, &shader, NULL);

	shader->SetVector("lightPosition", &D3DXVECTOR4(DirectX9->GetLightPosition(), 1));
	shader->SetVector("cameraPosition", &D3DXVECTOR4(camera->GetPosition(), 1));
	shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
	shader->SetTexture("defaultMap", texture);
}

SpecularShader::~SpecularShader()
{

}

void SpecularShader::Update()
{
	shader->SetTexture("defaultMap", texture);
	shader->SetVector("lightPosition", &D3DXVECTOR4(DirectX9->GetLightPosition(), 1));
	shader->SetVector("cameraPosition", &D3DXVECTOR4(camera->GetPosition(), 1));
}

void SpecularShader::SetAmbient(D3DXCOLOR ambient)
{
	ambientColor = ambient;

	shader->SetVector("ambientColor", &D3DXVECTOR4(ambientColor));
}

void SpecularShader::SetTexture(LPDIRECT3DTEXTURE9 texture)
{
	this->texture = texture;

	shader->SetTexture("defaultMap", texture);
}