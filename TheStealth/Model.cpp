#include "Model.h"
#include "DirectX9.h"
#include "Camera.h"
#include "TextureManager.h"

Model::Model(Camera* camera, string modelPath, string texturePath)
{
	LPD3DXBUFFER mtrlBuffer = NULL;

	D3DXLoadMeshFromXA(
		modelPath.c_str(),
		D3DXMESH_SYSTEMMEM,
		DirectX9->GetDevice(),
		NULL,
		&mtrlBuffer,
		NULL,
		&numMaterials,
		&mesh);

	D3DXMATERIAL* d3dxMaterials = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();

	meshMaterials = new D3DMATERIAL9[numMaterials];
	meshTextures = new LPDIRECT3DTEXTURE9[numMaterials];

	for (DWORD i = 0; i<numMaterials; i++)
	{
		meshMaterials[i] = d3dxMaterials[i].MatD3D;

		meshMaterials[i].Ambient = meshMaterials[i].Diffuse;

		meshTextures[i] = NULL;

		meshTextures[i] = TEXTURE->LoadTextureFromFile(texturePath.c_str());
	}

	mtrlBuffer->Release();

	shader = new SpecularShader(camera, meshTextures[0], D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}

Model::~Model()
{
	if (meshMaterials)
	{
		delete[] meshMaterials;
	}

	if (meshTextures)
	{
		delete[] meshTextures;
	}

	delete shader;
}

void Model::Update(float eTime)
{
	shader->Update();
}

void Model::Render()
{
	DxObject::Render();

	for (DWORD i = 0; i<numMaterials; i++)
	{
		UINT numPasses;
		shader->Start(&numPasses);

		for (UINT j = 0; j < numPasses; ++j)
		{
			shader->GetShader()->BeginPass(j);
			mesh->DrawSubset(i);
			shader->GetShader()->EndPass();
		}

		shader->End();
	}
}