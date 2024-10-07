#ifndef _CAMERA_H_
#define _CAMERA_H_

#include <d3d9.h>
#include <d3dx9.h>

class Camera
{
private:

	D3DXVECTOR3			position;
	D3DXVECTOR3			look;
	D3DXVECTOR3			up;
	D3DXVECTOR3			right;

	D3DXQUATERNION		orientation;

	D3DXMATRIX			viewMatrix;
	D3DXMATRIX			projectionMatrix;
	D3DXMATRIX			billboardMatrix;

	float				shakeFrequency;
	float				shakeSpeed;
	float				shakeFactor;
	float				shakeRad;

protected:

	static D3DXVECTOR3* TransformAxis(D3DXQUATERNION* orientation, D3DXVECTOR3* axis);
	static D3DXVECTOR3* TransformDirection(D3DXQUATERNION* orientation, D3DXVECTOR3* direction);
	void CalcDirectionVector();

public:

	Camera();
	~Camera();

	void MoveTo(float x, float y, float z);

	void MoveLocalX(float distance);
	void MoveLocalY(float distance);
	void MoveLocalZ(float distance);

	void RotateX(float degree);
	void RotateY(float degree);
	void RotateZ(float degree);

	bool Shake(float eTime, float shakeFrequency, float shakeSpeed, float shakeFactor);

	void SmoothRotate(D3DXQUATERNION quatTarget, float speedMultiple, float eTime);
	void SmoothTranslate(D3DXVECTOR3 target, float speedMultiple, float eTime);

	void UpdateView();
	void UpdateProjection(int fieldOfView, float aspect, float nearZ, float farZ);
	void UpdateProjection2(float fieldOfView, float aspect, float nearZ, float farZ);

public:

	D3DXMATRIX GetViewMatrix();
	D3DXMATRIX GetProjectionMatrix();
	D3DXMATRIX GetBillboardALL();
	D3DXMATRIX GetBillboardX();
	D3DXMATRIX GetBillboardY();
	D3DXMATRIX GetBillboardZ();
	D3DXVECTOR3 GetLookAt() { return look; }
	D3DXVECTOR3 GetPosition() { return position; }

};

#endif