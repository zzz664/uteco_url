#include "EvolutionTrail.h"
#include "EvolutionCore.h"
#include "EvolutionTextureManager.h"

EVTrail::EVTrail(std::string path, int slices, float scale)
{
	_texture = EVTextureManager->LoadTextureFromFile(path);

	_slices = slices;
	_scale = scale;

	_rom1 = new TRAILVERTEX[slices];
	_rom2 = new TRAILVERTEX[slices];
	
	_trail = new TRAILVERTEX[slices * 2];

	for (int i = 0; i < slices; ++i)
	{
		_rom1[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);
		_rom2[i].pos = D3DXVECTOR3(0.0f, 0.0f, 0.0f);

		_rom1[i].tex = D3DXVECTOR2(0.0f, 0.0f);
		_rom2[i].tex = D3DXVECTOR2(0.0f, 0.0f);
	}
}

EVTrail::~EVTrail()
{
	delete[] _rom1;
	delete[] _rom2;
	delete[] _trail;
}

void EVTrail::Update()
{
	EVGameObject::Update();

	_v[0].pos = Parent()->Position();

	for (int i = 2; i >= 0; --i)
	{
		_v[i + 1] = _v[i];
	}

	D3DXVec3CatmullRom(&_rom1[0].pos,
		&_v[0].pos,
		&_v[1].pos,
		&_v[2].pos,
		&_v[3].pos, (float)(0) / _slices);

	_rom1[0].pos += Parent()->Right() * (_scale / 2);
	_rom1[0].tex = D3DXVECTOR2(0.0f, 0.0f);

	D3DXVec3CatmullRom(&_rom2[0].pos,
		&_v[0].pos,
		&_v[1].pos,
		&_v[2].pos,
		&_v[3].pos, (float)(0) / _slices);

	_rom2[0].pos -= Parent()->Right() * (_scale / 2);
	_rom2[0].tex = D3DXVECTOR2(1.0f, 0.0f);

	for (int i = (_slices - 2); i >= 0; --i)
	{
		_rom1[i].tex = D3DXVECTOR2(1.0f / i, 0.0f);
		_rom1[i + 1] = _rom1[i];

		_rom2[i].tex = D3DXVECTOR2(1.0f / i, 1.0f);
		_rom2[i + 1] = _rom2[i];
	}


	for (int i = 0; i < _slices; ++i)
	{
		_trail[i * 2 + 0] = _rom1[i];
		_trail[i * 2 + 1] = _rom2[i];
	}
}

void EVTrail::Render()
{
	D3DXMATRIX world;
	D3DXMatrixIdentity(&world);
	EVSystem->DirectDevice()->SetTransform(D3DTS_WORLD, &world);

	EVSystem->DirectDevice()->SetFVF(D3DFVF_XYZ | D3DFVF_TEX1);

	EVSystem->DirectDevice()->SetTexture(0, _texture);

	EVSystem->DirectDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, true);

	EVSystem->DirectDevice()->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	EVSystem->DirectDevice()->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	EVSystem->DirectDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	EVSystem->DirectDevice()->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, (_slices * 2) - 2, _trail, sizeof(TRAILVERTEX));

	EVSystem->DirectDevice()->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	EVSystem->DirectDevice()->SetRenderState(D3DRS_ALPHABLENDENABLE, false);
}