#include "TestScene.h"
#include "InputManager.h"
#include "DirectX9.h"

TestScene::TestScene()
{
	camera = new Camera();
	camera->MoveTo(0.0f, 100.0f, -30.0f);

	skybox = new Skybox(camera);
	skybox->Create();
	AddObject(skybox);

	water = new Water(camera, 100000.0f);
	water->SetNormalScale(0.2);
	water->SetNormalSpeed(0.0f, 0.0f);
	water->SetTextureScale(25);
	water->SetReflectionAmount(0.5f);
	AddObject(water);

	jet = new MyJet(camera);
	jet->isExist = true;
	jet->SetPosition(0.0f, 100.0f, -3000.0f);
	jet->Initialize(100.0f, 30.0f, 180.0f);
	AddObject(jet);

	testJet = new Jet(camera, 0);
	testJet->SetPosition(0.0f, 200.0f, 0.0f);

	missile = new Missile(camera, testJet);
	AddObject(missile);

	Jet* tmp[8] = { NULL, NULL, NULL, NULL, NULL, NULL, NULL, NULL};

	testExplode = new ImageAnimation(camera, "Resource/Particles/Explosion/", 89, 30.0f);
	testExplode->SetScale(10.0f, 10.0f, 0.0f);
}

TestScene::~TestScene()
{
	delete testJet;
	delete camera;
}

void TestScene::Update(float eTime)
{
	Scene::Update(eTime);

	testJet->MoveLocalZ(200.0f * eTime);
	
	camera->SmoothTranslate(jet->GetPosition() + jet->GetUp() * 6.0f - jet->GetForward() * 15.0f, 10.0f, eTime);
	camera->SmoothRotate(jet->GetRotation(), 10.0f, eTime);

	D3DXVECTOR3 vDir = jet->GetPosition() - testJet->GetPosition();
	
	float dot = D3DXVec3Dot(&jet->GetPosition(), &testJet->GetPosition());
	float scale = D3DXVec3Length(&jet->GetPosition()) * D3DXVec3Length(&testJet->GetPosition());
	float cos = dot / scale;

	if (vDir.z < 0.0f && DxObject::Distance(jet->GetPosition(), testJet->GetPosition()) < 1500.0f && cos < D3DXToRadian(90.0f))
	{
		missile->isExist = true;
	}
	else
	{
		missile->isExist = false;
		missile->SetPosition(jet->GetPosition());
	}

	if (missile->hit)
	{
		static D3DXVECTOR3 pos = missile->GetPosition();
		testExplode->SetPosition(pos);
		testExplode->Update(eTime);
	}

}

void TestScene::Render()
{
	skybox->Render();
	water->Render();
	testJet->Render();
	jet->Render();
	if (!missile->hit)
		missile->Render();
	if (missile->hit)
	{
		testExplode->Render();
	}
}