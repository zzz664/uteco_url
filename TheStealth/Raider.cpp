#include "Raider.h"
#include "DirectX9.h"
#include "InputManager.h"
#include "../Core/DXUT.h"
#include "../LowLib/Log.h"

Raider::Raider(DxObject* player, DxObject* objects[])
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();
	
	raider = new Sprite("Resource/Ingame/mini_map.png");
	AddChild(raider, false);

	this->player = player;

	for (int i = 0; i < 8; ++i)
	{
		entity[i].sprite = new Sprite("Resource/Ingame/enemy.png");
		AddChild(entity[i].sprite, false);

		entity[i].object = objects[i];
		entity[i].isVisible = true;
	}
}

Raider::~Raider()
{

}

void Raider::SetTarget(DxObject* objects[])
{
	for (int i = 0; i < 8; ++i)
	{
		if (objects[i]->isExist == true)
		{
			entity[i].object = objects[i];
			entity[i].isVisible = true;
		}
	}
}

void Raider::Update(float eTime)
{
	DxObject2D::Update(eTime);

	D3DXVECTOR2 vDir;
	D3DXMATRIX rotMatrix;
	int i;
	for (i = 0; i < 8; ++i)
	{
		if (entity[i].object == NULL) continue;

		D3DXVECTOR2 eV = D3DXVECTOR2(entity[i].object->GetPosition().x, entity[i].object->GetPosition().z);
		D3DXVECTOR2 pV = D3DXVECTOR2(player->GetPosition().x, player->GetPosition().z);

		vDir = eV - pV;

		D3DXVECTOR2 tmp = vDir;
		D3DXVec2Normalize(&tmp, &tmp);

		D3DXQUATERNION quat;

		D3DXQuaternionRotationYawPitchRoll(&quat, 0.0f, 0.0f, D3DXToRadian(player->GetEulerRotation().y));

		D3DXMatrixRotationQuaternion(&rotMatrix, &quat);

		D3DXVec2TransformCoord(&vDir, &vDir, &rotMatrix);

		entity[i].sprite->SetPosition(
			vDir.x * ((128 * ratioX) / 1000.0f) + (89 * ratioX),
			-vDir.y * ((129 * ratioY) / 1000.0f) + (89 * ratioY));

		float distance = D3DXVec2Length(&vDir);

		if (distance <= 500 * ratioX)
		{
			entity[i].isVisible = true;
		}

		else
		{
			entity[i].isVisible = false;
		}
	}
}

void Raider::Render()
{
	DxObject2D::Render();

	raider->Render();
	for (int i = 0; i < 8; ++i)
	{
		if (entity[i].object != NULL && entity[i].isVisible)
		{
			entity[i].sprite->Render();
		}
	}
}