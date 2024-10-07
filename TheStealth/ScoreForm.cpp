#include "ScoreForm.h"
#include "DirectX9.h"
#include "Time.h"

ScoreForm::ScoreForm()
{
	ratioX = DirectX9->GetRatioX();
	ratioY = DirectX9->GetRatioY();

	teamA_score = 0;
	teamB_score = 0;

	m = 10;
	s = -1.0f;

	scoreForm = new Sprite("Resource/Ingame/score_form.png");

	scoreFont = new Font("KoPubµ¸¿òÃ¼ Bold", 2, 50.0f);
	timeFont = new Font("KoPubµ¸¿òÃ¼ Bold", 2, 40.0f);

	scoreFont->SetPosition(50 * ratioX, 30 * ratioY);
	timeFont->SetPosition(320 * ratioX, 55 * ratioY);

	AddChild(scoreForm, false);
	AddChild(scoreFont);
	AddChild(timeFont);
}

ScoreForm::~ScoreForm()
{

}

void ScoreForm::Update(float eTime)
{
	DxObject2D::Update(eTime);

	if (s <= -1.0f)
	{
		m -= 1;
		s = 59.0f;
	}

	s -= eTime;

	timeFont->SetText("%d : %.f", m, s);

}

void ScoreForm::Render()
{
	DxObject2D::Render();

	scoreForm->Render();

	scoreFont->SetPosition(170 * ratioX, 35 * ratioY);
	scoreFont->SetText("%d", teamA_score);
	scoreFont->Render();

	scoreFont->SetPosition(500 * ratioX, 35 * ratioY);
	scoreFont->SetText("%d", teamB_score);
	scoreFont->Render();

	timeFont->Render();
}

void ScoreForm::SetScore(int teamA, int teamB)
{
	teamA_score = teamA;
	teamB_score = teamB;
}