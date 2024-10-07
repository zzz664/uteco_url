#include "ResultScene.h"
#include "DirectX9.h"

ResultScene::ResultScene()
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	font = new Font("KoPubµ¸¿òÃ¼ Medium", 2, 50.0f);
	font2 = new Font("KoPubµ¸¿òÃ¼ Medium", 1, 30.0f);
	AddObject2D(font);
	AddObject2D(font2);

	{
		background[0] = new Sprite("Resource/Result/background.png");
		background[1] = new Sprite("Resource/Result/form.png");
		background[2] = new Sprite("Resource/Result/image-01.png");
		background[3] = new Sprite("Resource/Result/image-02.png");
		background[4] = new Sprite("Resource/Result/gradient.png");
		background[5] = new Sprite("Resource/Result/gradient.png");

		background[1]->SetPosition(250 * ratioX, 150 * ratioY);
		background[2]->SetPosition(260 * ratioX, 270 * ratioY);
		background[3]->SetPosition(965 * ratioX, 270 * ratioY);
		background[4]->SetPosition(270 * ratioX, 300 * ratioY);
		background[5]->SetPosition(975 * ratioX, 300 * ratioY);

		for (int i = 0; i < 6; ++i) AddObject2D(background[i], false);
	}

	{
		for (int i = 0; i < 2; ++i)
		{
			info[i] = new ResultInfo();

			info[i]->SetData(0, "¾¾¹ß", 0, 10);
			info[i]->SetData(1, "¾¾¹ß", 0, 10);
			info[i]->SetData(2, "¾¾¹ß", 0, 10);
			info[i]->SetData(3, "¾¾¹ß", 0, 10);

			AddObject2D(info[i]);
		}

		info[0]->SetPosition(330 * ratioX, 480 * ratioY);
		info[1]->SetPosition(1050 * ratioX, 480 * ratioY);

	}
}

ResultScene::~ResultScene()
{

}

void ResultScene::Update(float eTime)
{
	Scene::Update(eTime);
}

void ResultScene::Render()
{
	for (int i = 0; i < 6; ++i) background[i]->Render();

	for(int i = 0; i < 2; ++i) info[i]->Render();

	font->SetColor(D3DXCOLOR(0.8f, 0.55f, 0.0f, 1.0f));
	font->SetPosition(915 * ratioX, 180 * ratioY);
	font->SetText("ÀüÅõ °á°ú");
	font->Render();

	font->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
	font->SetPosition(570 * ratioX, 305 * ratioY);
	font->SetText("½Â¸®");
	font->Render();

	font->SetPosition(1300 * ratioX, 305 * ratioY);
	font->SetText("ÆÐ¹è");
	font->Render();

	font2->SetPosition(280 * ratioX, 780 * ratioY);
	font2->SetText("TOTAL KILL                    %d", 0);
	font2->Render();

	font2->SetPosition(279 * ratioX, 820 * ratioY);
	font2->SetText("TOTAL DEATH                %d", 0);
	font2->Render();

	font2->SetPosition(1455 * ratioX, 780 * ratioY);
	font2->SetText("TOTAL KILL                    %d", 0);
	font2->Render();

	font2->SetPosition(1454 * ratioX, 820 * ratioY);
	font2->SetText("TOTAL DEATH                %d", 0);
	font2->Render();
}