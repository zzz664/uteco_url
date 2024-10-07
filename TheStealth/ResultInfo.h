#ifndef _RESULTINFO_H_
#define _RESULTINFO_H_

#include "Font.h"

class ResultInfo : public DxObject2D
{

	Font* font;

	struct InfoType
	{
		string name;
		int k;
		int d;
	};

	InfoType info[4];

	float ratioX;
	float ratioY;

public:
	
	ResultInfo();
	~ResultInfo();

	void SetData(int index, string name, int k, int d);

	void Update(float eTime);
	void Render();
};

#endif