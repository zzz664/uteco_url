#include "Trail.h"
#include "DirectX9.h"

Trail::Trail(int slices, float scale)
{
	device = DirectX9->GetDevice();

	this->slices = slices;
	this->scale = scale;

	rom1 = new VertexType[slices];
	rom2 = new VertexType[slices];

	trail = new VertexType[slices * 2];

	for (int i = 0; i < slices; ++i)
	{
		rom1[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		rom2[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		rom1[i].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		rom2[i].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
	}
}

Trail::~Trail()
{
	delete[] rom1;
	delete[] rom2;
	delete[] trail;
}

void Trail::Update(float eTime)
{
	DxObject::Update(eTime);

	v[0].pos = parent->GetPosition();

	for (int i = 2; i >= 0; --i)
	{
		v[i + 1] = v[i];
	}

	D3DXVec3CatmullRom(&rom1[0].pos,
		&v[0].pos,
		&v[1].pos,
		&v[2].pos,
		&v[3].pos, (float)(0) / slices);

	rom1[0].pos += parent->GetRight() * (scale / 2);
	rom1[0].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	D3DXVec3CatmullRom(&rom2[0].pos,
		&v[0].pos,
		&v[1].pos,
		&v[2].pos,
		&v[3].pos, (float)(0) / slices);

	rom2[0].pos -= parent->GetRight() * (scale / 2);
	rom2[0].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);

	for (int i = (slices - 2); i >= 0; --i)
	{
		rom1[i].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		rom1[i + 1] = rom1[i];

		rom2[i].color = D3DXVECTOR4(1.0f, 1.0f, 1.0f, 1.0f);
		rom2[i + 1] = rom2[i];
	}


	for (int i = 0; i < slices; ++i)
	{
		trail[i * 2 + 0] = rom1[i];
		trail[i * 2 + 1] = rom2[i];
	}
}

void Trail::Render()
{
	DxObject* p = parent;
	parent = NULL;
	
	DxObject::Render();

	parent = p;

	device->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	device->SetTexture(0, NULL);

	device->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	device->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	device->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	device->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, (slices * 2) - 2, trail, sizeof(VertexType));

	device->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	device->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}