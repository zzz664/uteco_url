#include "HPForm.h"
#include "DirectX9.h"

HPForm::HPForm()
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	healthPoint = 100.0f;

	for (int i = 0; i < 5; ++i) hpValue[i] = 20.0f;

	font = new Font("KoPubµ¸¿òÃ¼ Bold", 2, 50.0f);
	font->SetPosition(90 * ratioX, 40 * ratioY);

	hpForm = new Sprite("Resource/Ingame/HP_form.png");

	int j;

	for (int i = 0, j = 4; i < 5; ++i, j--)
	{
		hp[i] = new Sprite("Resource/Ingame/HP.png");
		hp[i]->SetPosition(0.0f, (41 * j + 48) * ratioY);

		AddChild(hp[i], false);
	}
	
	AddChild(hpForm, false);
	AddChild(font);
}

HPForm::~HPForm()
{

}

void HPForm::Update(float eTime)
{
	DxObject2D::Update(eTime);

	currentIndex = (int)(healthPoint / 20);
	if (currentIndex == 5)
	{
		for (int i = 0; i < 5; ++i)
		{
			hpValue[i] = 20.0f;
			hp[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}

	for (int i = 4; i > currentIndex; --i)
	{
		hpValue[i] = 0.0f;
		hp[i]->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 0.0f));
	}

	hp[currentIndex]->SetColor(
		D3DXCOLOR(
		1.0f,
		1.0f,
		1.0f,
		hpValue[currentIndex] / 20 * 100 * eTime));
		//healthPoint/100.0f));

	font->SetText("%.1f%%", healthPoint);
}

void HPForm::Render()
{
	DxObject2D::Render();

	hpForm->Render();

	for (int i = 0; i < 5; ++i) hp[i]->Render();

	font->Render();
}

void HPForm::SetHP(float hp)
{
	healthPoint = hp;

	currentIndex = (int)(healthPoint / 20.0f);

	float deltaHP = 0.0f;

	for (int i = -1; i < currentIndex; ++i)
	{
		deltaHP = (int)hp % 20;
	}

	hpValue[currentIndex] = deltaHP;
}