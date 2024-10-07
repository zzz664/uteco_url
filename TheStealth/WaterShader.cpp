#include "WaterShader.h"
#include "Camera.h"
#include "DirectX9.h"
#include "Time.h"
#include "TextureManager.h"

WaterShader::WaterShader(Camera* camera)
{
	this->camera = camera;

	path = "Shader/water.fx";

	D3DXCreateEffectFromFileA(DirectX9->GetDevice(), path.c_str(), NULL, NULL, 0, NULL, &shader, NULL);

	shader->SetTexture("texture0", TEXTURE->LoadTextureFromFile("Resource/Water/waterNormal2.dds"));
	shader->SetTexture("texture1", TEXTURE->LoadTextureFromFile("Resource/Skybox/Top.png"));
}

WaterShader::~WaterShader()
{

}

void WaterShader::Update(float eTime)
{
	shader->SetFloat("time", TIME->CurrentTime());
	shader->SetVector("cameraPosition", &D3DXVECTOR4(camera->GetPosition(), 1));
}