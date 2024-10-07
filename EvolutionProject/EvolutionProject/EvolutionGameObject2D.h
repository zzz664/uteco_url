#ifndef _EVOLUTIONGAMEOBJECT2D_H_
#define _EVOLUTIONGAMEOBJECT2D_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <list>

using namespace std;

class EVGameObject2D
{
protected:
	std::string				_tag;

	EVGameObject2D*			_parent;
	list<EVGameObject2D*>	_child;

	D3DXMATRIX				_transformMatrix;
	D3DXVECTOR2				_scale;
	D3DXVECTOR2				_scalingCenter;
	float					_rotation;
	D3DXVECTOR2				_rotationCenter;
	D3DXVECTOR2				_position;

	bool					_update;

public:
	//************************************<Description>***********************************************
	//	EVGameObject2D클래스의 생성자이다.
	EVGameObject2D();

	//************************************<Description>***********************************************
	//	 EVGameObject2D클래스의 소멸자이다.
	virtual ~EVGameObject2D();

	//************************************<Description>***********************************************
	//	매 프레임마다 호출되는 함수로 실시간으로 바뀌는 정보를 처리한다.
	//	EVGameObject2D클래스의 Update함수는 자식(하위) 노드들의 Update함수를 호출한다.
	virtual void Update();

	//************************************<Description>***********************************************
	//	매 프레임 마다 호출되는 함수로 GameObject2D의 이동, 회전, 크기 변환을 수행한다.
	//	또한 부모(상위) 노드가 존재한다면 자신의 변환행렬에 부모의 변환행렬을 누적해서 곱한다.
	virtual void Render();

public:

	//************************************<Description>***********************************************
	//	이 함수는 자식(하위) 노드로 GameObject2D를 추가하는 함수이다.
	//	isUpdate인자는 현재 자식으로 추가하려는 GameObject가 업데이트 될 것인지의 여부이며
	//	Default값은 true이므로 넣지않으면 기본적으로 true가 들어가고
	//	false를 넣을경우 부모(상위) 노드가 업데이트 될 때 업데이트 되지 않는다.
	void PushChildObject(EVGameObject2D* gameObject, std::string tag, bool isUpdate = true);

	//************************************<Description>***********************************************
	//	이 함수는 자식(하위) 노드로 추가된 GameObject2D를 다시 최상위로 빼는 함수이다.
	//	isErase인자는 자식을 꺼낼 때 메모리에서 지울것인지의 여부이며
	//	Default값은 true이므로 넣지않으면 GameObject를 빼고난 후 메모리상에서 지운다.
	//	false를 넣을경우 최상위에 위치하게 된다.
	void PopChildObject(std::string tag, bool isErase = true);

	EVGameObject2D* FindChildObject(std::string tag);

public:

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 변환행렬을 수정하는 함수이다.
	//	인자로 들어오는 D3DXMATRIX transformMatrix의 값으로 GameObject의 변환행렬의 값에 대입한다.
	void TransformMatrix(D3DXMATRIX transformMatrix)	{ _transformMatrix = transformMatrix; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 크기를 수정하는 함수이다.
	//	인자로 들어오는 D3DXVECTOR3 scale의 값으로 GameObject2D의 크기 값에 대입한다.
	void Scale(D3DXVECTOR2 scale)						{ _scale = scale; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 각도를 수정하는 함수이다.
	//	인자로 들어오는 float rotation의 값으로 GameObject2D의 회전 값에 대입한다.
	void Rotation(float rotation)						{ _rotation = rotation; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 위치값을 수정하는 함수이다.
	//	인자로 들어오는 D3DXVECTOR2 position의 값을 GameObject2D의 위치값에 대입한다.
	void Position(D3DXVECTOR2 position)					{ _position = position; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 크기가 변할 때 기준이 되는 점을 수정하는 함수이다.
	//	인자로 들어오는 D3DXVECTOR2 scalingCenter의 값을 GameObject2D의 크기변환중심값에 대입한다.
	void ScalingCenter(D3DXVECTOR2 scalingCenter)		{ _scalingCenter = scalingCenter; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D가 회전할 때 중심이 되는 점을 수정하는 함수이다.
	//	인자로 들어오는 D3DXVECTOR2 rotationCenter의 값을 GameObject2D의 회전중심값에 대입한다.
	void RotationCenter(D3DXVECTOR2 rotationCenter)		{ _rotationCenter = rotationCenter; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 업데이트 여부를 수정하는 함수이다.
	void SetUpdate(bool isUpdate)						{ _update = isUpdate; }

	template<typename X, typename Y>
	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 크기를 수정하는 함수이다.
	//	각각의 인자는 x축, y축의 크기변환값이다.
	void Scale(X x, Y y)
	{
		_scale.x = static_cast<float>(x);
		_scale.y = static_cast<float>(y);
	}

	template<typename X>
	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 각도를 수정하는 함수이다.
	//	인자는 회전각도이다.
	void Rotation(X x)
	{
		_rotation = static_cast<float>(x);
	}

	template<typename X, typename Y>
	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 크기가 변할 때 기준이 되는 점을 수정하는 함수이다.
	//	각각의 인자는 x축, y축의 크기변환중심점의 위치값이다.
	void ScalingCenter(X x, Y y)
	{
		_scalingCenter.x = static_cast<float>(x);
		_scalingCenter.y = static_cast<float>(y);
	}

	template<typename X, typename Y>
	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D가 회전할 때 중심이 되는 점을 수정하는 함수이다.
	//	각각의 인자는 x축, y축의 회전중심점의 위치값
	void RotationCenter(X x, Y y)
	{
		_rotationCenter.x = static_cast<float>(x);
		_rotationCenter.y = static_cast<float>(y);
	}

	template<typename X, typename Y>
	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 위치값을 수정하는 함수이다.
	//	각각의 인자는 x축, y축의 위치값이다.
	void Position(X x, Y y)
	{
		_position.x = static_cast<float>(x);
		_position.y = static_cast<float>(y);
	}

	void Tag(std::string tag)
	{
		_tag = tag;
	}


public:
	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 변환행렬을 반환하는 함수이다.
	D3DXMATRIX  TransformMatrix()	{ return _transformMatrix; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 크기값을 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR2
	D3DXVECTOR2 Scale()				{ return _scale; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 x축 크기값을 반환하는 함수이다.
	//	반환타입 : float
	float		ScaleX()			{ return _scale.x; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 y축 크기값을 반환하는 함수이다.
	//	반환타입 : float
	float		ScaleY()			{ return _scale.y; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 회전값을 반환하는 함수이다.
	//	반환타입 : float
	float		Rotation()			{ return _rotation; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 위치값을 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR2
	D3DXVECTOR2 Position()			{ return _position; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의  x축 위치값을 반환하는 함수이다.
	//	반환타입 : float
	float		PositionX()			{ return _position.x; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 y축 위치값을 반환하는 함수이다.
	//	반환타입 : float
	float		PositionY()			{ return _position.y; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 크기변환중심점위치를 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR2
	D3DXVECTOR2 ScalingCenter()		{ return _scalingCenter; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 x축 크기변환중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		ScalingCenterX()	{ return _scalingCenter.x; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 y축 크기변환중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		ScalingCenterY()	{ return _scalingCenter.y; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 회전중심점위치를 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR2
	D3DXVECTOR2 RotationCenter()	{ return _rotationCenter; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 x축 회전중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		RotationCenterX()	{ return _rotationCenter.x; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 y축 회전중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		RotationCenterY()	{ return _rotationCenter.y; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject2D의 업데이트 여부를 반환하는 함수이다.
	//	반환타입 : bool
	bool		IsUpdate()			{ return _update; }

	//************************************<Description>***********************************************
	//	이 함수는 현재GameObject2D의 부모의 포인터를 반환하는 함수이다.
	//	반환타입 : EVGameObject2D
	EVGameObject2D* Parent()		{ return _parent; }

	std::string		Tag()			{ return _tag; }

};

#endif