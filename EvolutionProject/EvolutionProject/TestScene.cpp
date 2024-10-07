#include "TestScene.h"
#include "EvolutionTime.h"
#include "EvolutionInput.h"
#include "EvolutionCore.h"
#include "EvolutionMath.h"
#include "EvolutionEffectManager.h"
#include "EvolutionTextureManager.h"

TestScene::TestScene()
{
	skyBox = new EVSkyBox;
	skyBox->Create();
	PushGameObject(skyBox, "SkyBox", false);

	camera = new EVCamera;
	camera->Initialize(skyBox);
	camera->MoveLocalForward(-5);

	model = new EVModel("Assets/Model/map.X");
	PushGameObject(model, "Map", false);
	model->Position(0, -10, 0);

	t1 = new TestObject();
	PushGameObject(t1, "t1");
	t1->Position(2, 0, 0);

	t2 = new TestObject();
	PushGameObject(t2, "t2");

	sprite = new EVSprite2D("Assets/Texture/mapTexture.jpg");
	PushGameObject2D(sprite, "sprite", false);
	sprite->Scale(0.1, 0.1);
}

TestScene::~TestScene()
{
	delete camera;
}

void TestScene::Update()
{
	EVScene::Update();

	static float speed = 5;
	static float t3 = 0.0f;

	if (EVInput->GetKey(VK_LEFT))
	{
		t1->Translate(t1->Right() * -speed * EVTime->DeltaTime());
	}
	if (EVInput->GetKey(VK_RIGHT))
	{
		t1->Translate(t1->Right() * speed * EVTime->DeltaTime());
	}
	if (EVInput->GetKey(VK_UP))
	{
		t1->RotateLocalForward(-90 * EVTime->DeltaTime());
	}
	if (EVInput->GetKey(VK_DOWN))
	{
		t1->RotateLocalForward(90 * EVTime->DeltaTime());
	}

	D3DXVECTOR3 dir;
	float gap;

	if (EVMath::SphereToSphereCollision(t1->Collider(), t2->Collider(), &dir, &gap))
	{
		EVSystem->SystemLog()->Log("asd");
		t1->Position(t1->Position() - dir * t1->Radius() * gap);
		speed = 10.0f / 5;
	}
	else
	{
		speed = 10.0f;
	}
}

void TestScene::Render()
{
	skyBox->Render();
	sprite->Render();
	t1->Render();
	t2->Render();

	//model->Render();
}