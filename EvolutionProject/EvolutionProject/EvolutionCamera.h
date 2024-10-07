#ifndef _TESTCAMERA_H_
#define _TESTCAMERA_H_

#include <d3dx9.h>

#include "EvolutionSkyBox.h"
#include "EvolutionTime.h"

class EVCamera
{

private:

	D3DXVECTOR3			_position;			
	D3DXVECTOR3			_look;
	D3DXVECTOR3			_up;

	D3DXQUATERNION		_orientation;	

	D3DXMATRIX			_viewMatrix;			
	D3DXMATRIX			_projectionMatrix;
	D3DXMATRIX			_billboardMatrix;

	EVSkyBox*			_skyBox;


protected:

	static D3DXVECTOR3* TransformAxis(D3DXQUATERNION* orientation, D3DXVECTOR3* axis);

public:

	EVCamera();
	virtual ~EVCamera();

	void	Initialize(EVSkyBox* skyBox);

public:

	void	MoveLocalRight(float distance);
	void	MoveLocalUp(float distance);		
	void	MoveLocalForward(float distance);	

	void	MoveTo(D3DXVECTOR3 target);

	template<typename X, typename Y, typename Z>
	void	MoveTo(X x, Y y, Z z)
	{
		_position = D3DXVECTOR3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));

		UpdateView();
	}

	void	RotateRight(float degree);	
	void	RotateUp(float degree);		
	void	RotateForward(float degree);	

	bool	SmoothRotate(D3DXQUATERNION quatTarget, float speedMultiple = 1.0f);

	bool	SmoothTranslate(D3DXVECTOR3 target, float speedMultiple = 1.0f);

	template<typename X, typename Y, typename Z>
	bool	SmoothTranslate(X x, Y y, Z z, float speedMultiple = 1.0f)
	{
		D3DXVECTOR3 target(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));

		if (_position == target)
		{
			return false;
		}

		D3DXVec3Lerp(&_position, &_position, &target, EVTime->DeltaTime() * speedMultiple);

		UpdateView();

		return true;
	}

	void	Rotation(D3DXQUATERNION rotation);
	void	Rotation(D3DXVECTOR3 rotation);

	template<typename X, typename Y, typename Z>
	void	Rotation(X x, Y y, Z z)
	{
		D3DXQUATERNION quatRotation;
		D3DXQuaternionIdentity(&quatRotation);

		D3DXQuaternionRotationYawPitchRoll(&quatRotation, 
			static_cast<float>(D3DXToRadian(y)), 
			static_cast<float>(D3DXToRadian(x)), 
			static_cast<float>(D3DXToRadian(z)));

		_orientation = quatRotation;

		UpdateView();
	}

public:

	void	Position(D3DXVECTOR3 position)
	{
		_position = position;

		UpdateView();
	}

	void	UpdateView();
	void	UpdateProjection(int fieldOfView, float aspect, float nearZ, float farZ);

public:

	D3DXMATRIX	ViewMatrix()		{ return _viewMatrix; }
	D3DXMATRIX	ProjectionMatrix()	{ return _projectionMatrix; }
	D3DXMATRIX	BillboardMatrix()	{ return _billboardMatrix; }

	D3DXQUATERNION Rotation()		{ return _orientation; }
	D3DXVECTOR3 Position()			{ return _position; }
};

#endif