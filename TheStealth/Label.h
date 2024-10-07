#ifndef _LABEL_H_
#define _LABEL_H_

#include "DxObject2D.h"
#include "Font.h"
#include <string>

using namespace std;

class Label : public DxObject2D
{
private:

	Font* font;

	string normal;
	string point;

	D3DXCOLOR normalColor;
	D3DXCOLOR pointColor;

	float size;

public:

	Label(string normal, D3DXCOLOR color1, string point, D3DXCOLOR color2, float size);
	~Label();

	void Update(float eTime);
	void Render();

	void SetNormalColor(D3DXCOLOR color);
	void SetPointColor(D3DXCOLOR color);

	D3DXCOLOR GetNormalColor() { return normalColor; }
	D3DXCOLOR GetPointColor() { return pointColor; }
};

#endif