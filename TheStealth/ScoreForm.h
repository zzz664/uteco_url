#ifndef _SCOREFORM_H_
#define _SCOREFORM_H_

#include "Sprite.h"
#include "Font.h"

class ScoreForm : public DxObject2D
{

private:

	Sprite* scoreForm;

	Font*	scoreFont;
	Font*	timeFont;

	int teamA_score;
	int teamB_score;


	float ratioX;
	float ratioY;

public:

	ScoreForm();
	~ScoreForm();

	void Update(float eTime);
	void Render();

	void SetScore(int teamA, int teamB);
	int GetScore_TeamA() { return teamA_score; }
	int GetScore_TeamB() { return teamB_score; }

	int m;
	float s;
};

#endif