#ifndef _KILLLOG_H
#define _KILLLOG_H_

#include "Font.h"

class KillLog : public DxObject2D
{
	
	Font* font;

	string log[5];

	float visibleTime;
	float alpha;

	bool isChange;

	float ratioX;
	float ratioY;

public:
	
	KillLog();
	~KillLog();

	void SetLog(string killer, string killee);

	void Update(float eTime);
	void Render();
};

#endif