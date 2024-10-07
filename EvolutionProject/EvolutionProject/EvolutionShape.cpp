#include "EvolutionShape.h"
#include "EvolutionCore.h"

EVShape::EVShape(std::string shape, D3DXCOLOR ambientColor)
{
	_diffuse = new EVDiffuse(ambientColor);
	PushChildObject(_diffuse, "DiffuseShader");

	if (shape == "Cube")
	{
		D3DXCreateBox(EVSystem->DirectDevice(), 1.0f, 1.0f, 1.0f, &_mesh, NULL);
	}
	else if (shape == "Sphere")
	{
		D3DXCreateSphere(EVSystem->DirectDevice(), 0.5f, 20, 10, &_mesh, NULL);
	}
	else if (shape == "Cylinder")
	{
		D3DXCreateCylinder(EVSystem->DirectDevice(), 0.5f, 0.5f, 1.0f, 20, 10, &_mesh, NULL);
		RotateLocalRight(90);
	}
}

EVShape::~EVShape()
{
	_mesh->Release();
}

void EVShape::Update()
{
	EVGameObject::Update();
}

void EVShape::Render(D3DXMATRIX* combinedMatrix)
{
	EVGameObject::Render(combinedMatrix);

	UINT numPasses = 0;
	_diffuse->Start(&numPasses);

	for (int i = 0; i < numPasses; ++i)
	{
		_diffuse->Shader()->BeginPass(i);
		{
			_mesh->DrawSubset(i);
		}
		_diffuse->Shader()->EndPass();
	}
	_diffuse->End();
}