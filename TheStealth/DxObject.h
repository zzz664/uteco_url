#ifndef _DXOBJECT_H_
#define _DXOBJECT_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <d3d10_1.h>
#include <list>

using namespace std;

class DxObject
{
protected:

	DxObject*		parent;
	list<DxObject*> child;

	D3DXMATRIX		worldMatrix;
	D3DXVECTOR3		scale;
	D3DXVECTOR3		scalingCenter;
	D3DXVECTOR3		eulerAngle;
	D3DXVECTOR3		rotationCenter;
	D3DXQUATERNION	quaternionAngle;
	D3DXVECTOR3		position;

	D3DXVECTOR3		forward;
	D3DXVECTOR3		right;
	D3DXVECTOR3		up;

	bool			update;
	bool			remove;

protected:

	void				CalcDirectionVector();
	D3DXVECTOR3			TransformDirection(D3DXQUATERNION*, D3DXVECTOR3*);

public:

	DxObject();
	virtual ~DxObject();

	virtual void Update(float eTime);
	virtual void Render();

	void Translate(D3DXVECTOR3 vector);
	void Translate(D3DXVECTOR3 target, float speed, float eTime);
	void Rotate(D3DXQUATERNION target, float spped);

	void SmoothTranslate(D3DXVECTOR3 target, float speedMultiple = 1.0f);
	void SmoothRotate(D3DXQUATERNION target, float speedMultiple = 1.0f);

	void MoveLocalZ(float distance);

	void RotateLocalX(float degree);
	void RotateLocalY(float degree);
	void RotateLocalZ(float degree);

	static float Distance(D3DXVECTOR3 v1, D3DXVECTOR3 v2);

	bool isExist;

public:

	void AddChild(DxObject* object, bool isUpdate = true);
	void RemoveChild(DxObject* object);

	bool IsUpdate() { return update; }
	void SetUpdate(bool update) { this->update = update; }

	void SetWorldMatrix(D3DXMATRIX worldMatrix);
	void SetScale(float x, float y, float z);
	void SetPosition(float x, float y, float z);
	void SetPosition(D3DXVECTOR3 pos);
	void SetRotation(float w, float x, float y, float z);
	void SetRotation(D3DXQUATERNION rot);
	void SetScalingCenter(float x, float y, float z);
	void SetRotationCenter(float x, float y, float z);

	D3DXMATRIX		GetWorldMatrix()	{ return worldMatrix; }
	D3DXVECTOR3		GetScale()			{ return scale; }
	D3DXVECTOR3		GetEulerRotation()	{ return eulerAngle; }
	D3DXQUATERNION	GetRotation()		{ return quaternionAngle; }
	D3DXVECTOR3		GetPosition()		{ return position; }
	D3DXVECTOR3		GetScalingCenter()	{ return scalingCenter; }
	D3DXVECTOR3		GetRotationCenter()	{ return rotationCenter; }

	D3DXVECTOR3		GetForward()		{ return forward; }
	D3DXVECTOR3		GetRight()			{ return right; }
	D3DXVECTOR3		GetUp()				{ return up; }

	DxObject*		GetParent()			{ return parent; }

};

#endif