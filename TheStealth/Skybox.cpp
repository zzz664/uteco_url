#include "Skybox.h"
#include "Camera.h"
#include "DirectX9.h"
#include "TextureManager.h"

Skybox::Skybox(Camera* camera)
{
	this->camera = camera;

	device = DirectX9->GetDevice();

	char textureNames[6][64] =
	{
		"Resource/Skybox/Top.jpg",
		"Resource/Skybox/Front.jpg",
		"Resource/Skybox/Back.jpg",
		"Resource/Skybox/Right.jpg",
		"Resource/Skybox/Left.jpg",
		"Resource/Skybox/Bottom.jpg"
	};

	for (int i = 0; i < 6; ++i)
	{
		textures[i] = TEXTURE->LoadTextureFromFile(textureNames[i]);
	}

	vertexBuffer = NULL;
}
Skybox::~Skybox()
{
	vertexBuffer->Release();
}
void Skybox::Create()
{
	device->CreateVertexBuffer(
		24 * sizeof(SKYBOXVERTEX),
		0,
		(D3DFVF_XYZ | D3DFVF_TEX1),
		D3DPOOL_DEFAULT,
		&vertexBuffer,
		NULL);

	SKYBOXVERTEX vertices[24] =
	{
		{ -5000.0f, 5000.0f, -5000.0f, 0.0f, 0.0f },		// Top vertices
		{ 5000.0f, 5000.0f, -5000.0f, 1.0f, 0.0f },
		{ -5000.0f, 5000.0f, 5000.0f, 0.0f, 1.0f },
		{ 5000.0f, 5000.0f, 5000.0f, 1.0f, 1.0f },

		{ -5000.0f, 5000.0f, 5000.0f, 0.0f, 0.0f },		// Front vertices
		{ 5000.0f, 5000.0f, 5000.0f, 1.0f, 0.0f },
		{ -5000.0f, -5000.0f, 5000.0f, 0.0f, 1.0f },
		{ 5000.0f, -5000.0f, 5000.0f, 1.0f, 1.0f },

		{ 5000.0f, 5000.0f, -5000.0f, 0.0f, 0.0f },		// Back vertices
		{ -5000.0f, 5000.0f, -5000.0f, 1.0f, 0.0f },
		{ 5000.0f, -5000.0f, -5000.0f, 0.0f, 1.0f },
		{ -5000.0f, -5000.0f, -5000.0f, 1.0f, 1.0f },

		{ -5000.0f, 5000.0f, -5000.0f, 0.0f, 0.0f },		// Left vertices
		{ -5000.0f, 5000.0f, 5000.0f, 1.0f, 0.0f },
		{ -5000.0f, -5000.0f, -5000.0f, 0.0f, 1.0f },
		{ -5000.0f, -5000.0f, 5000.0f, 1.0f, 1.0f },
			 
		{ 5000.0f, 5000.0f, 5000.0f, 0.0f, 0.0f },		// Right vertices
		{ 5000.0f, 5000.0f, -5000.0f, 1.0f, 0.0f },
		{ 5000.0f, -5000.0f, 5000.0f, 0.0f, 1.0f },
		{ 5000.0f, -5000.0f, -5000.0f, 1.0f, 1.0f },

		{ -5000.0f, -5000.0f, 5000.0f, 0.0f, 0.0f },		// Bottom vertices
		{ 5000.0f, -5000.0f, 5000.0f, 1.0f, 0.0f },
		{ -5000.0f, -5000.0f, -5000.0f, 0.0f, 1.0f },
		{ 5000.0f, -5000.0f, -5000.0f, 1.0f, 1.0f }
	};

	VOID* pVertices;
	vertexBuffer->Lock(0, 24 * sizeof(SKYBOXVERTEX), (void**)&pVertices, 0);

	memcpy(pVertices, vertices, 24 * sizeof(SKYBOXVERTEX));

	vertexBuffer->Unlock();
}
void Skybox::BuildVertex(SKYBOXVERTEX* vtx, float x, float y, float z, float u, float v)
{
	vtx->x = x;
	vtx->y = y;
	vtx->z = z;
	vtx->u = u;
	vtx->v = v;
}
void Skybox::Update(float eTime)
{
	DxObject::Update(eTime);

	SetPosition(
		camera->GetPosition().x, 
		camera->GetPosition().y, 
		camera->GetPosition().z);
}
void Skybox::Render()
{
	DxObject::Render();

	device->SetRenderState(D3DRS_ZENABLE, false);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	device->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DX_FILTER_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DX_FILTER_LINEAR);
	device->SetSamplerState(0, D3DSAMP_MINFILTER, D3DX_FILTER_LINEAR);

	device->SetFVF((D3DFVF_XYZ | D3DFVF_TEX1));
	device->SetStreamSource(0, vertexBuffer, 0, sizeof(SKYBOXVERTEX));

	for (int i = 0; i < 6; i++)
	{
		D3DMATERIAL9 mtrl;

		ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));

		mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
		mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
		mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
		mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;

		device->SetMaterial(&mtrl);
		device->SetTexture(0, textures[i]);
		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

	device->SetRenderState(D3DRS_ZENABLE, true);
}