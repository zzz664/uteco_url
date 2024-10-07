#include "KillDeathInfo.h"
#include "DirectX9.h"
#include "Def.h"
#include "Server\ServerManager.h"

KillDeathInfo::KillDeathInfo()
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	nickname = new Font("KoPubµ¸¿òÃ¼ Medium", 2, 30.0f);
	nickname->SetPosition(100.0f * ratioX, 10.0f * ratioY);
	AddChild(nickname);

	kd = new Font("KoPubµ¸¿òÃ¼ Medium", 2, 20.0f);
	kd->SetPosition(100.0f * ratioX, 40.0f * ratioY);
	AddChild(kd);

	form = new Sprite("Resource/InGame/kill_death_info.png");
	AddChild(form);

	nickname->SetText(wstToStr(ServerManager::getInstance().NickName).c_str());
	kill = 0;
	death = 0;
	kd->SetText("K : 0 / D : 0");
}

KillDeathInfo::~KillDeathInfo()
{

}

void KillDeathInfo::Update(float eTime)
{
	DxObject2D::Update(eTime);
}

void KillDeathInfo::Render()
{
	DxObject2D::Render();

	form->Render();
	nickname->Render();
	kd->Render();
}

void KillDeathInfo::SetData(int k, int d)
{
	kill = k;
	death = d;
	kd->SetText("K : %d   D : %d", kill, death);
}