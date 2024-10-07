#include "ResultInfo.h"
#include "DirectX9.h"

ResultInfo::ResultInfo()
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	font = new Font("KoPubµ¸¿òÃ¼ Medium", 1, 25.0f);
	AddChild(font);

	for (int i = 0; i < 4; ++i)
	{
		info[i].name = "";
		info[i].k = 0;
		info[i].d = 0;
	}
}

ResultInfo::~ResultInfo()
{

}

void ResultInfo::Update(float eTime)
{
	DxObject2D::Update(eTime);
}

void ResultInfo::Render()
{
	DxObject2D::Render();

	font->SetColor(D3DXCOLOR(0.8f, 0.55f, 0.0f, 1.0f));
	font->SetPosition(0.0f, 0.0f);
	font->SetText("NAME");
	font->Render();

	font->SetPosition(310 * ratioX, 0.0f);
	font->SetText("KILL");
	font->Render();

	font->SetPosition(510 * ratioX, 0.0f);
	font->SetText("DEATH");
	font->Render();

	for (int i = 0; i < 4; ++i)
	{
		if (strcmp(info[i].name.c_str(), "") == 1)
		{
			char tmp[5];

			font->SetColor(D3DXCOLOR(1.0f, 1.0f, 1.0f, 1.0f));

			font->SetPosition(0.0f, ((i + 1) * 40.0f + 25.0f) * ratioY);
			font->SetText(info[i].name.c_str());
			font->Render();

			font->SetPosition(310 * ratioX, ((i + 1) * 40.0f + 25.0f) * ratioY);
			font->SetText(itoa(info[i].k, tmp, 10));
			font->Render();

			font->SetPosition(510 * ratioX, ((i + 1) * 40.0f + 25.0f) * ratioY);
			font->SetText(itoa(info[i].d, tmp, 10));
			font->Render();
		}
	}
}

void ResultInfo::SetData(int index, string name, int k, int d)
{
	info[index].name = name;
	info[index].k = k;
	info[index].d = d;
}