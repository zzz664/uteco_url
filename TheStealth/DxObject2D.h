#ifndef _DXOBJECT2D_H_
#define _DXOBJECT2D_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <list>


using namespace std;

class DxObject2D
{
protected:

	DxObject2D*			parent;
	list<DxObject2D*>	child;

	D3DXMATRIX			worldMatrix;

	D3DXVECTOR2			scale;
	D3DXVECTOR2			scalingCenter;
	D3DXVECTOR2			rotationCenter;
	D3DXVECTOR2			position;

	float				rotation;

	bool				update;

public:

	DxObject2D();
	virtual ~DxObject2D();

	virtual void Update(float eTime);
	virtual void Render();

public:

	void AddChild(DxObject2D* object, bool update = true);

	bool IsUpdate() { return update; }
	void SetUpdate(bool update) { this->update = update; }

	void SmoothTranslate(D3DXVECTOR2 target, float speedMultiple = 1.0f);
	void SmoothScale(D3DXVECTOR2 target, float speedMultiple = 1.0f);

public:

	void SetWorldMatrix(D3DXMATRIX worldMatrix);
	void SetScale(float x, float y);
	void SetRotation(float rotation);
	void SetPosition(float x, float y);
	void SetScalingCenter(float x, float y);
	void SetRotationCenter(float x, float y);

	D3DXMATRIX  GetWorldMatrix()	{ return worldMatrix; }
	D3DXVECTOR2 GetScale()			{ return scale; }
	float		GetRotation()		{ return rotation; }
	D3DXVECTOR2 GetPosition()		{ return position; }
	D3DXVECTOR2 GetScalingCenter()	{ return scalingCenter; }
	D3DXVECTOR2 GetRotationCenter()	{ return rotationCenter; }
	DxObject2D* GetParent()			{ return parent; }
};

#endif