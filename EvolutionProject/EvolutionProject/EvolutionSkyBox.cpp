#include "EvolutionSkyBox.h"
#include "EvolutionCore.h"
#include "EvolutionTextureManager.h"

EVSkyBox::EVSkyBox() 
{
	char textureNames[6][64] = 
	{
		"Assets/SkyBox/Top.png",
		"Assets/SkyBox/Front.png",
		"Assets/SkyBox/Back.png",
		"Assets/SkyBox/Right.png",
		"Assets/SkyBox/Left.png",
		"Assets/SkyBox/Bottom.png" 
	};

	for (int i = 0; i < 6; ++i) 
	{
		textures[i] = EVTextureManager->LoadTextureFromFile(textureNames[i]);
	}

	vertexBuffer = NULL;
}
EVSkyBox::~EVSkyBox() 
{
	vertexBuffer->Release();
	for (int i = 0; i < 6; i++) 
	{
		textures[i]->Release();
	}
}
void EVSkyBox::Create() 
{
	EVSystem->DirectDevice()->CreateVertexBuffer(
		24 * sizeof(SKYBOXVERTEX), 
		0, 
		(D3DFVF_XYZ | D3DFVF_TEX1),
		D3DPOOL_DEFAULT, 
		&vertexBuffer, 
		NULL);

	SKYBOXVERTEX vertices[24] = 
	{
		{ -500.0f, 500.0f, -500.0f, 0.0f, 0.0f },		// Top vertices
		{ 500.0f, 500.0f, -500.0f, 1.0f, 0.0f },
		{ -500.0f, 500.0f, 500.0f, 0.0f, 1.0f },
		{ 500.0f, 500.0f, 500.0f, 1.0f, 1.0f },

		{ -500.0f, 500.0f, 500.0f, 0.0f, 0.0f },		// Front vertices
		{ 500.0f, 500.0f, 500.0f, 1.0f, 0.0f },
		{ -500.0f, -500.0f, 500.0f, 0.0f, 1.0f },
		{ 500.0f, -500.0f, 500.0f, 1.0f, 1.0f },

		{ 500.0f, 500.0f, -500.0f, 0.0f, 0.0f },		// Back vertices
		{ -500.0f, 500.0f, -500.0f, 1.0f, 0.0f },
		{ 500.0f, -500.0f, -500.0f, 0.0f, 1.0f },
		{ -500.0f, -500.0f, -500.0f, 1.0f, 1.0f },

		{ -500.0f, 500.0f, -500.0f, 0.0f, 0.0f },		// Left vertices
		{ -500.0f, 500.0f, 500.0f, 1.0f, 0.0f },
		{ -500.0f, -500.0f, -500.0f, 0.0f, 1.0f },
		{ -500.0f, -500.0f, 500.0f, 1.0f, 1.0f },

		{ 500.0f, 500.0f, 500.0f, 0.0f, 0.0f },		// Right vertices
		{ 500.0f, 500.0f, -500.0f, 1.0f, 0.0f },
		{ 500.0f, -500.0f, 500.0f, 0.0f, 1.0f },
		{ 500.0f, -500.0f, -500.0f, 1.0f, 1.0f },

		{ -500.0f, -500.0f, 500.0f, 0.0f, 0.0f },		// Bottom vertices
		{ 500.0f, -500.0f, 500.0f, 1.0f, 0.0f },
		{ -500.0f, -500.0f, -500.0f, 0.0f, 1.0f },
		{ 500.0f, -500.0f, -500.0f, 1.0f, 1.0f }
	};

	VOID* pVertices;
	vertexBuffer->Lock(0, 24 * sizeof(SKYBOXVERTEX), (void**)&pVertices, 0);

	memcpy(pVertices, vertices, 24 * sizeof(SKYBOXVERTEX));

	vertexBuffer->Unlock();
}
void EVSkyBox::BuildVertex(SKYBOXVERTEX* vtx, float x, float y, float z, float u, float v) 
{
	vtx->x = x;
	vtx->y = y;
	vtx->z = z;
	vtx->u = u;
	vtx->v = v;
}
void EVSkyBox::Update() 
{
	EVGameObject::Update();
}
void EVSkyBox::Render() 
{
	EVGameObject::Render();
	
	EVSystem->DirectDevice()->SetRenderState(D3DRS_LIGHTING, true);

	EVSystem->DirectDevice()->SetRenderState(D3DRS_ZENABLE, false);

	EVSystem->DirectDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	EVSystem->DirectDevice()->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_CLAMP);
	EVSystem->DirectDevice()->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_CLAMP);

	EVSystem->DirectDevice()->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DX_FILTER_LINEAR);
	EVSystem->DirectDevice()->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DX_FILTER_LINEAR);
	EVSystem->DirectDevice()->SetSamplerState(0, D3DSAMP_MINFILTER, D3DX_FILTER_LINEAR);

	EVSystem->DirectDevice()->SetFVF((D3DFVF_XYZ | D3DFVF_TEX1));
	EVSystem->DirectDevice()->SetStreamSource(0, vertexBuffer, 0, sizeof(SKYBOXVERTEX));

	for (int i = 0; i < 6; i++) 
	{
		D3DMATERIAL9 mtrl;

		ZeroMemory(&mtrl, sizeof(D3DMATERIAL9));

		mtrl.Diffuse.r = mtrl.Ambient.r = 1.0f;
		mtrl.Diffuse.g = mtrl.Ambient.g = 1.0f;
		mtrl.Diffuse.b = mtrl.Ambient.b = 1.0f;
		mtrl.Diffuse.a = mtrl.Ambient.a = 1.0f;
		
		EVSystem->DirectDevice()->SetMaterial(&mtrl);
		EVSystem->DirectDevice()->SetTexture(0, textures[i]);
		EVSystem->DirectDevice()->DrawPrimitive(D3DPT_TRIANGLESTRIP, i * 4, 2);
	}

	EVSystem->DirectDevice()->SetRenderState(D3DRS_ZENABLE, true);

	EVSystem->DirectDevice()->SetRenderState(D3DRS_LIGHTING, false);
}