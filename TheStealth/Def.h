#ifndef _DEF_H_
#define _DEF_H_

#include <string>

#include "Camera.h"

using namespace std;

inline string wstToStr(const wchar_t* pStr)
{
	string strOut;
	int len = -1;

	int nChars = WideCharToMultiByte(CP_ACP, 0,
		pStr, len, NULL, 0, NULL, NULL);

	strOut.resize(nChars);
	WideCharToMultiByte(CP_ACP, 0, pStr, len,
		const_cast<char*>(strOut.c_str()), nChars, NULL, NULL);

	return strOut;
}

inline D3DXVECTOR2 Convert3Dto2D(Camera* camera, D3DXVECTOR3 target)
{
	D3DXMATRIX ViewProjection = camera->GetViewMatrix() * camera->GetProjectionMatrix();
	D3DXVECTOR3 vector = target;

	D3DXVec3TransformCoord(&vector, &vector, &ViewProjection);

	vector.x += 1;
	vector.y += 1;

	D3DVIEWPORT9 vp;

	DirectX9->GetDevice()->GetViewport(&vp);

	vector.x = (vp.Width * (vector.x)) / 2.0f + vp.X;
	vector.y = (vp.Height * (2.0f - vector.y)) / 2.0f + vp.Y;

	return D3DXVECTOR2(vector.x, vector.y);
}

#endif