#include "Shader.h"
#include "DirectX9.h"

Shader::Shader()
{

}

Shader::~Shader()
{
	shader->Release();
}

void Shader::Update()
{

}

void Shader::Start(UINT* numPasses)
{

	D3DXMATRIX world, view, projection;

	DirectX9->GetDevice()->GetTransform(D3DTS_WORLD, &world);
	DirectX9->GetDevice()->GetTransform(D3DTS_VIEW, &view);
	DirectX9->GetDevice()->GetTransform(D3DTS_PROJECTION, &projection);

	shader->SetMatrix("worldMatrix", &world);
	shader->SetMatrix("viewMatrix", &view);
	shader->SetMatrix("projectionMatrix", &projection);

	shader->Begin(numPasses, NULL);
}

void Shader::End()
{
	shader->End();

	DirectX9->GetDevice()->SetVertexShader(NULL);
	DirectX9->GetDevice()->SetPixelShader(NULL);
}

ID3DXEffect* Shader::GetShader()
{
	return shader;
}

std::string Shader::GetPath()
{
	return path;
}