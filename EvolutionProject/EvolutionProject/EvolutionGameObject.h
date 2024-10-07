#ifndef _EVOLUTIONGAMEOBJECT_H_
#define _EVOLUTIONGAMEOBJECT_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <list>
#include <string>

#include "EvolutionTime.h"

using namespace std;

class EVGameObject
{
protected:
	std::string			_tag;

	EVGameObject*		_parent;
	list<EVGameObject*> _child;

	D3DXMATRIX			_transformMatrix;
	D3DXVECTOR3			_scale;
	D3DXVECTOR3			_scalingCenter;
	D3DXVECTOR3			_eulerAngle;
	D3DXVECTOR3			_rotationCenter;
	D3DXQUATERNION		_quaternionAngle;
	D3DXVECTOR3			_position;

	D3DXVECTOR3			_forward;
	D3DXVECTOR3			_right;
	D3DXVECTOR3			_up;

	bool				_update;

protected:

	void				CalcDirectionVector();

public:
	//************************************<Description>***********************************************
	//	EVGameObject클래스의 생성자이다.
	EVGameObject();

	//************************************<Description>***********************************************
	//	 EVGameObject클래스의 소멸자이다.
	virtual ~EVGameObject();

	//************************************<Description>***********************************************
	//	매 프레임마다 호출되는 함수로 실시간으로 바뀌는 정보를 처리한다.
	//	EVGameObject클래스의 Update함수는 자식(하위) 노드들의 Update함수를 호출한다.
	virtual void Update();

	//************************************<Description>***********************************************
	//	매 프레임 마다 호출되는 함수로 GameObject의 이동, 회전, 크기 변환을 수행한다.
	//	또한 부모(상위) 노드가 존재한다면 자신의 변환행렬에 부모의 변환행렬을 누적해서 곱한다.
	//	그리고 최종 변환행렬에 월드변환을 수행한다.
	//	인자로 들어가는 D3DXMATRIX* combinedMatrix의 Default는 NULL이므로 
	//	아무것도 넣지않으면 위의 동작을 하고 추가로 인자를 넣게되면
	//	자신의 변환행렬 * 인자로 들어온 누적행렬 * 부모(상위) 노드의 변환행렬을 수행한다.
	//	이 인자는 애니메이션 매쉬의 장비착용을 위한 인자이므로, 일반적으로 인자를 넣지않는다.
	virtual void Render(D3DXMATRIX* combinedMatrix = NULL);

	//************************************<Description>***********************************************
	//	물체의 위치를 옮기는 함수이다.
	//	인자로 들어오는 vector를 물체의 위치값에 더해준다.
	//	ex) 물체->Translate(방향벡터 * 속도 * DeltaTime)을 한다면 방향벡터가 가르키는
	//	방향으로 초당 속도만큼 이동하게된다.
	void Translate(D3DXVECTOR3 vector);

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	물체의 위치를 옮기는 함수이다.
	//	인자로 들어오는 x, y, z값으로 벡터를 만들어 물체의 위치값에 더해준다.
	//	ex) 물체->Translate(방향벡터 * 속도 * DeltaTime)을 한다면 방향벡터가 가르키는
	//	방향으로 초당 속도만큼 이동하게된다.
	void Translate(X x, Y y, Z z)
	{
		_position += D3DXVECTOR3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
	}

	//************************************<Description>***********************************************
	//	물체를 목표지점까지 부드럽게 움직이는 함수이다.
	//	물체의 위치를 인자로 들어오는 target의 위치까지 보간한다.
	//	두번째 인자는 보간속도의 배수값이다. 숫자가 클수록 보간되는 속도가 빨라진다.
	bool SmoothTranslate(D3DXVECTOR3 target, float speedMultiple = 1.0f);

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	물체를 목표지점까지 부드럽게 움직이는 함수이다.
	//	물체의 위치를 인자로 들어오는 x, y, z의 값으로 target을 만들어
	//	target의 위치까지 보간한다.
	//	두번째 인자는 보간속도의 배수값이다. 숫자가 클수록 보간되는 속도가 빨라진다.
	bool SmoothTranslate(X x, Y y, Z z, float speedMultiple = 1.0f)
	{
		D3DXVECTOR3 target(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));

		if (_position == target)
		{
			return false;
		}

		D3DXVec3Lerp(&_position, &_position, &target, EVTime->DeltaTime() * speedMultiple);

		return true;
	}

	//************************************<Description>***********************************************
	//	물체를 목표각도까지 부드럽게 회전시키는 함수이다.
	//	물체의 위치를 인자로 들어오는 target의 각도까지 보간한다.
	//	목표각도를 인자로 넣을땐 D3DXVECTOR3타입으로 넣고
	//	각각의 원소가 x축 회전각도, y축 회전각도, z축 회전각도 가 되도록 넣어야한다.
	//	라디안값으로 넣으면 안됨
	//	두번째 인자는 보간속도의 배수값이다. 숫자가 클수록 보간되는 속도가 빨라진다.
	bool SmoothRotate(D3DXVECTOR3 target, float speedMultiple = 1.0f);

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	물체를 목표각도까지 부드럽게 회전시키는 함수이다.
	//	물체의 위치를 인자로 들어오는 x, y, z의값으로 벡터를 만들어 보간한다.
	//	목표각도를 인자로 넣을땐 x축 회전각도, y축 회전각도, z축 회전각도 가 되도록 넣어야한다.
	//	라디안값으로 넣으면 안됨
	//	두번째 인자는 보간속도의 배수값이다. 숫자가 클수록 보간되는 속도가 빨라진다.
	bool SmoothRotate(X x, Y y, Z z, float speedMultiple = 1.0f)
	{
		D3DXVECTOR3 target(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
		_eulerAngle = target;

		D3DXQUATERNION targetQuaternion;

		D3DXQuaternionIdentity(&targetQuaternion);

		D3DXQuaternionRotationYawPitchRoll(&targetQuaternion, D3DXToRadian(target.y), D3DXToRadian(target.x), D3DXToRadian(target.z));

		if (_quaternionAngle == targetQuaternion)
		{
			return false;
		}

		D3DXQuaternionSlerp(&_quaternionAngle, &_quaternionAngle, &targetQuaternion, EVTime->DeltaTime() * speedMultiple);

		CalcDirectionVector();

		return true;
	}

	void RotateLocalRight(float degree);
	void RotateLocalUp(float degree);
	void RotateLocalForward(float degree);

	void RotateWorldRight(float degree);
	void RotateWorldUp(float degree);
	void RotateWorldForward(float degree);

	void RotationUp(float degree);
	void RotationRight(float degree);
	void RotationForward(float degree);

public:

	//************************************<Description>***********************************************
	//	이 함수는 자식(하위) 노드로 GameObject를 추가하는 함수이다.
	//	isUpdate인자는 현재 자식으로 추가하려는 GameObject가 업데이트 될 것인지의 여부이며
	//	Default값은 true이므로 넣지않으면 기본적으로 true가 들어가고
	//	false를 넣을경우 부모(상위) 노드가 업데이트 될 때 업데이트 되지 않는다.
	void PushChildObject(EVGameObject* gameObject, std::string tag, bool isUpdate = true);

	//************************************<Description>***********************************************
	//	이 함수는 자식(하위) 노드로 추가된 GameObject를 다시 최상위로 빼는 함수이다.
	//	isErase인자는 자식을 꺼낼 때 메모리에서 지울것인지의 여부이며
	//	Default값은 true이므로 넣지않으면 GameObject를 빼고난 후 메모리상에서 지운다.
	//	false를 넣을경우 최상위에 위치하게 된다.
	void PopChildObject(std::string tag, bool isErase = true);

	EVGameObject* FindChildObject(std::string tag);

public:

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 변환행렬을 수정하는 함수이다.
	//	인자로 들어오는 D3DXMATRIX transformMatrix의 값으로 GameObject의 변환행렬의 값에 대입한다.
	void TransformMatrix(D3DXMATRIX transformMatrix)	{ _transformMatrix = transformMatrix; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 크기를 수정하는 함수이다.
	//	인자로 들어오는 D3DXVECTOR3 scale의 값으로 GameObject의 크기 값에 대입한다.
	void Scale(D3DXVECTOR3 scale)						{ _scale = scale; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 위치값을 수정하는 함수이다.
	//	인자로 들어오는 D3DXVECTOR3 position의 값을 GameObject의 위치값에 대입한다.
	void Position(D3DXVECTOR3 position)					{ _position = position; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 크기가 변할 때 기준이 되는 점을 수정하는 함수이다.
	//	인자로 들어오는 D3DXVECTOR3 scalingCenter의 값을 GameObject의 크기변환중심값에 대입한다.
	void ScalingCenter(D3DXVECTOR3 scalingCenter)		{ _scalingCenter = scalingCenter; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject가 회전할 때 중심이 되는 점을 수정하는 함수이다.
	//	인자로 들어오는 D3DXVECTOR3 rotationCenter의 값을 GameObject의 회전중심값에 대입한다.
	void RotationCenter(D3DXVECTOR3 rotationCenter)		{ _rotationCenter = rotationCenter; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 업데이트 여부를 수정하는 함수이다.
	void SetUpdate(bool isUpdate)						{ _update = isUpdate; }

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 크기를 수정하는 함수이다.
	//	각각의 인자는 x축, y축, z축의 크기변환값이다.
	void Scale(X x, Y y, Z z)
	{
		_scale.x = static_cast<float>(x);
		_scale.y = static_cast<float>(y);
		_scale.z = static_cast<float>(z);
	}

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 크기가 변할 때 기준이 되는 점을 수정하는 함수이다.
	//	각각의 인자는 x축, y축, z축의 크기변환중심점의 위치값이다.
	void ScalingCenter(X x, Y y, Z z)
	{
		_scalingCenter.x = static_cast<float>(x);
		_scalingCenter.y = static_cast<float>(y);
		_scalingCenter.z = static_cast<float>(z);
	}

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	이 함수는 GameObject가 회전할 때 중심이 되는 점을 수정하는 함수이다.
	//	각각의 인자는 x축, y축, z축의 회전중심점의 위치값
	void RotationCenter(X x, Y y, Z z)
	{
		_rotationCenter.x = static_cast<float>(x);
		_rotationCenter.y = static_cast<float>(y);
		_rotationCenter.z = static_cast<float>(z);
	}

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 위치값을 수정하는 함수이다.
	//	각각의 인자는 x축, y축, z축의 위치값이다.
	void Position(X x, Y y, Z z)
	{
		_position.x = static_cast<float>(x);
		_position.y = static_cast<float>(y);
		_position.z = static_cast<float>(z);
	}
	
	void Tag(std::string tag)
	{
		_tag = tag;
	}

public:
	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 변환행렬을 반환하는 함수이다.
	D3DXMATRIX  TransformMatrix()	{ return _transformMatrix; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 크기값을 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR3
	D3DXVECTOR3 Scale()				{ return _scale; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 x축 크기값을 반환하는 함수이다.
	//	반환타입 : float
	float		ScaleX()			{ return _scale.x; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 y축 크기값을 반환하는 함수이다.
	//	반환타입 : float
	float		ScaleY()			{ return _scale.y; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 z축 크기값을 반환하는 함수이다.
	//	반환타입 : float
	float		ScaleZ()			{ return _scale.z; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 회전값을 오일러 각으로 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR3
	D3DXVECTOR3 EulerRotation()		{ return _eulerAngle; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 x축 회전값을 오일러 각으로 반환하는 함수이다.
	//	반환타입 : float
	float		EulerRotationX()	{ return _eulerAngle.x; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 y축 회전값을 오일러 각으로 반환하는 함수이다.
	//	반환타입 : float
	float		EulerRotationY()	{ return _eulerAngle.y; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 z축 회전값을 오일러 각으로 반환하는 함수이다.
	//	반환타입 : float
	float		EulerRotationZ()	{ return _eulerAngle.z; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 위치값을 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR3
	D3DXVECTOR3 Position()			{ return _position; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의  x축 위치값을 반환하는 함수이다.
	//	반환타입 : float
	float		PositionX()			{ return _position.x; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 y축 위치값을 반환하는 함수이다.
	//	반환타입 : float
	float		PositionY()			{ return _position.y; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 z축 위치값을 반환하는 함수이다.
	//	반환타입 : float
	float		PositionZ()			{ return _position.z; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 크기변환중심점위치를 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR3
	D3DXVECTOR3 ScalingCenter()		{ return _scalingCenter; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 x축 크기변환중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		ScalingCenterX()	{ return _scalingCenter.x; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 y축 크기변환중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		ScalingCenterY()	{ return _scalingCenter.y; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 z축 크기변환중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		ScalingCenterZ()	{ return _scalingCenter.z; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 회전중심점위치를 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR3
	D3DXVECTOR3 RotationCenter()	{ return _rotationCenter; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 x축 회전중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		RotationCenterX()	{ return _rotationCenter.x; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 y축 회전중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		RotationCenterY()	{ return _rotationCenter.y; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 z축 회전중심점위치를 반환하는 함수이다.
	//	반환타입 : float
	float		RotationCenterZ()	{ return _rotationCenter.z; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 로컬 좌표계의 Z축 방향을 나타내는 벡터를 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR3
	D3DXVECTOR3	Forward()			{ return _forward; }
	
	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 로컬 좌표계의 X축 방향을 나타내는 벡터를 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR3
	D3DXVECTOR3 Right()				{ return _right; }
	
	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 로컬 좌표계의 Y축 방향을 나타내는 벡터를 반환하는 함수이다.
	//	반환타입 : D3DXVECTOR3
	D3DXVECTOR3 Up()				{ return _up; }

	//************************************<Description>***********************************************
	//	이 함수는 GameObject의 업데이트 여부를 반환하는 함수이다.
	//	반환타입 : bool
	bool		IsUpdate()			{ return _update; }

	//************************************<Description>***********************************************
	//	이 함수는 현재GameObject의 부모의 포인터를 반환하는 함수이다.
	//	반환타입 : EVGameObject
	EVGameObject* Parent()			{ return _parent; }

	D3DXQUATERNION Rotation()		{ return _quaternionAngle; }

	std::string		Tag()			{ return _tag; }

};

#endif