#ifndef _IMAGE_H_
#define _IMAGE_H_

#include "DxObject.h"
#include "TextureManager.h"
#include "TextureShader.h"

class Camera;

using namespace std;

enum BILLBOARD_STATE
{
	BILLBOARD_NONE,
	BILLBOARD_ALL,
	BILLBOARD_XY,
	BILLBOARD_X,
	BILLBOARD_Y,
	BILLBOARD_Z,
	END
};

class Image : public DxObject
{
private:

	Camera* camera;

	struct VertexType {
		float x, y, z;
		float u, v;
	};

	LPDIRECT3DDEVICE9		device;

	LPDIRECT3DTEXTURE9		texture;
	LPDIRECT3DVERTEXBUFFER9 vertexBuffer;

	TextureShader*			shader;

	D3DXVECTOR4				color;

	bool				useAlphaBlend;
	BILLBOARD_STATE		billboard_state;

public:

	Image(Camera* camera, string path);
	~Image();

	void Update(float eTime);
	void Render();

	void SetBillboardState(BILLBOARD_STATE state) { billboard_state = state; }
	void SetAlphaBlend(bool alphaBlend) { this->useAlphaBlend = alphaBlend; }
	void SetColor(float r, float g, float b, float a);

	D3DXCOLOR GetColor() { return color; }

};

#endif