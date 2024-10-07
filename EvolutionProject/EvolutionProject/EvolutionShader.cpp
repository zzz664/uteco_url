#include "EvolutionShader.h"
#include "EvolutionCore.h"

EVShader::EVShader()
{

}

EVShader::~EVShader()
{

}

void EVShader::Update()
{

}

void EVShader::Start(UINT* numPasses)
{

	D3DXMATRIX world, view, projection;

	EVSystem->DirectDevice()->GetTransform(D3DTS_WORLD, &world);
	EVSystem->DirectDevice()->GetTransform(D3DTS_VIEW, &view);
	EVSystem->DirectDevice()->GetTransform(D3DTS_PROJECTION, &projection);

	_shader->SetMatrix("worldMatrix", &world);
	_shader->SetMatrix("viewMatrix", &view);
	_shader->SetMatrix("projectionMatrix", &projection);

	_shader->Begin(numPasses, NULL);
}

void EVShader::End()
{
	_shader->End();

	EVSystem->DirectDevice()->SetVertexShader(NULL);
	EVSystem->DirectDevice()->SetPixelShader(NULL);
}

ID3DXEffect* EVShader::Shader()
{
	return _shader;
}

std::string EVShader::Path()
{
	return _path;
}