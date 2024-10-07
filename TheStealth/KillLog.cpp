#include "KillLog.h"
#include "DirectX9.h"

KillLog::KillLog()
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	font = new Font("KoPubµ¸¿òÃ¼ Medium", 2, 20.0f);
	AddChild(font);

	for (int i = 0; i < 5; ++i) log[i] = "";

	visibleTime = 0.0f;
	alpha = 1.0f;

	isChange = false;
}

KillLog::~KillLog()
{

}

void KillLog::Update(float eTime)
{
	DxObject2D::Update(eTime);

	visibleTime += eTime;

	if (visibleTime >= 3.0f)
	{
		if (alpha >= 0.0f)
		{
			alpha -= 0.3 * eTime;
			font->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, alpha));
		}

		if (alpha <= 0.0f && isChange == false)
		{
			for (int i = 0; i < 5; ++i) log[i] = "";
			isChange = true;
		}
	}
}

void KillLog::Render()
{
	DxObject2D::Render();

	for (int i = 0; i < 5; ++i)
	{
		font->SetPosition(0.0f, (i * 25.0f) * ratioY);
		font->SetText("%s", log[i].c_str());
		font->Render();
	}
}

void KillLog::SetLog(string killer, string killee)
{
	for (int i = 4; i >= 1; --i)
	{
		log[i] = log[i - 1];
	}

	log[0] = killer.c_str();
	log[0] += " Killed ";
	log[0] += killee.c_str();

	visibleTime = 0.0f;
	alpha = 1.0f;

	isChange = false;

	font->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));
}