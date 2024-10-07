#include "Image.h"
#include "Camera.h"
#include "DirectX9.h"
#include "Camera.h"
#include "EffectManager.h"

Image::Image(Camera* camera, string path)
{
	this->camera = camera;

	device = DirectX9->GetDevice();

	texture = TEXTURE->LoadTextureFromFile(path);

	shader = new TextureShader(texture);

	DirectX9->GetDevice()->CreateVertexBuffer(
		4 * sizeof(VertexType), 
		0, 
		(D3DFVF_XYZ | D3DFVF_TEX1),
		D3DPOOL_DEFAULT, 
		&vertexBuffer, 
		0);

	VertexType vertices[4] = {
		{ -1.0f, 1.0f, 0.0f, 0.0f, 0.0f },
		{ 1.0f, 1.0f, 0.0f, 1.0f, 0.0f },
		{ -1.0f, -1.0f, 0.f, 0.0f, 1.0f },
		{ 1.0f, -1.0f, 0.0f, 1.0f, 1.0f }
	};

	void* pVertices;

	vertexBuffer->Lock(0, 4 * sizeof(VertexType), (void**)&pVertices, 0);

	memcpy(pVertices, vertices, 4 * sizeof(VertexType));

	vertexBuffer->Unlock();

	useAlphaBlend = true;
	billboard_state = BILLBOARD_NONE;

	color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
}
Image::~Image() 
{
	vertexBuffer->Release();

	delete shader;
}

void Image::Update(float eTime) 
{
	shader->Update();
}

void Image::Render() 
{
	DxObject::Render();

	if (billboard_state != BILLBOARD_NONE)
	{
		D3DXMATRIX S;
		D3DXMatrixIdentity(&S);

		D3DXMatrixScaling(&S, scale.x, scale.y, scale.z);

		switch (billboard_state)
		{
		case BILLBOARD_ALL:
			S = S * camera->GetBillboardALL();
			break;

		case BILLBOARD_XY:
			S = S * (camera->GetBillboardX() * camera->GetBillboardY());
			break;

		case BILLBOARD_X:
			S = S * camera->GetBillboardX();
			break;

		case BILLBOARD_Y:
			S = S * camera->GetBillboardY();
			break;

		case BILLBOARD_Z:
			S = S * camera->GetBillboardZ();
			break;
		}

		D3DXMATRIX T;
		D3DXMatrixIdentity(&T);
		D3DXMatrixTranslation(&T, position.x, position.y, position.z);

		S *= T;

		device->SetTransform(D3DTS_WORLD, &S);
	}

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	device->SetFVF((D3DFVF_XYZ | D3DFVF_TEX1));

	device->SetStreamSource(0, vertexBuffer, 0, sizeof(VertexType));

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	if (useAlphaBlend) 
	{
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);
		device->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);
	}

	else
	{
		device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
		device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);
	}

	UINT numPasses = 0;
	shader->Start(&numPasses);

	for (UINT i = 0; i < numPasses; ++i)
	{
		shader->GetShader()->BeginPass(i);
		device->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);
		shader->GetShader()->EndPass();
	}

	shader->End();

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}

void Image::SetColor(float r, float g, float b, float a)
{
	color.x = r;
	color.y = g;
	color.z = b;
	color.w = a;

	shader->SetAmbient(D3DXCOLOR(color));
}