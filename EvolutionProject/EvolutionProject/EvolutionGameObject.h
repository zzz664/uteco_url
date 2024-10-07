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
	//	EVGameObjectŬ������ �������̴�.
	EVGameObject();

	//************************************<Description>***********************************************
	//	 EVGameObjectŬ������ �Ҹ����̴�.
	virtual ~EVGameObject();

	//************************************<Description>***********************************************
	//	�� �����Ӹ��� ȣ��Ǵ� �Լ��� �ǽð����� �ٲ�� ������ ó���Ѵ�.
	//	EVGameObjectŬ������ Update�Լ��� �ڽ�(����) ������ Update�Լ��� ȣ���Ѵ�.
	virtual void Update();

	//************************************<Description>***********************************************
	//	�� ������ ���� ȣ��Ǵ� �Լ��� GameObject�� �̵�, ȸ��, ũ�� ��ȯ�� �����Ѵ�.
	//	���� �θ�(����) ��尡 �����Ѵٸ� �ڽ��� ��ȯ��Ŀ� �θ��� ��ȯ����� �����ؼ� ���Ѵ�.
	//	�׸��� ���� ��ȯ��Ŀ� ���庯ȯ�� �����Ѵ�.
	//	���ڷ� ���� D3DXMATRIX* combinedMatrix�� Default�� NULL�̹Ƿ� 
	//	�ƹ��͵� ���������� ���� ������ �ϰ� �߰��� ���ڸ� �ְԵǸ�
	//	�ڽ��� ��ȯ��� * ���ڷ� ���� ������� * �θ�(����) ����� ��ȯ����� �����Ѵ�.
	//	�� ���ڴ� �ִϸ��̼� �Ž��� ��������� ���� �����̹Ƿ�, �Ϲ������� ���ڸ� �����ʴ´�.
	virtual void Render(D3DXMATRIX* combinedMatrix = NULL);

	//************************************<Description>***********************************************
	//	��ü�� ��ġ�� �ű�� �Լ��̴�.
	//	���ڷ� ������ vector�� ��ü�� ��ġ���� �����ش�.
	//	ex) ��ü->Translate(���⺤�� * �ӵ� * DeltaTime)�� �Ѵٸ� ���⺤�Ͱ� ����Ű��
	//	�������� �ʴ� �ӵ���ŭ �̵��ϰԵȴ�.
	void Translate(D3DXVECTOR3 vector);

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	��ü�� ��ġ�� �ű�� �Լ��̴�.
	//	���ڷ� ������ x, y, z������ ���͸� ����� ��ü�� ��ġ���� �����ش�.
	//	ex) ��ü->Translate(���⺤�� * �ӵ� * DeltaTime)�� �Ѵٸ� ���⺤�Ͱ� ����Ű��
	//	�������� �ʴ� �ӵ���ŭ �̵��ϰԵȴ�.
	void Translate(X x, Y y, Z z)
	{
		_position += D3DXVECTOR3(static_cast<float>(x), static_cast<float>(y), static_cast<float>(z));
	}

	//************************************<Description>***********************************************
	//	��ü�� ��ǥ�������� �ε巴�� �����̴� �Լ��̴�.
	//	��ü�� ��ġ�� ���ڷ� ������ target�� ��ġ���� �����Ѵ�.
	//	�ι�° ���ڴ� �����ӵ��� ������̴�. ���ڰ� Ŭ���� �����Ǵ� �ӵ��� ��������.
	bool SmoothTranslate(D3DXVECTOR3 target, float speedMultiple = 1.0f);

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	��ü�� ��ǥ�������� �ε巴�� �����̴� �Լ��̴�.
	//	��ü�� ��ġ�� ���ڷ� ������ x, y, z�� ������ target�� �����
	//	target�� ��ġ���� �����Ѵ�.
	//	�ι�° ���ڴ� �����ӵ��� ������̴�. ���ڰ� Ŭ���� �����Ǵ� �ӵ��� ��������.
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
	//	��ü�� ��ǥ�������� �ε巴�� ȸ����Ű�� �Լ��̴�.
	//	��ü�� ��ġ�� ���ڷ� ������ target�� �������� �����Ѵ�.
	//	��ǥ������ ���ڷ� ������ D3DXVECTOR3Ÿ������ �ְ�
	//	������ ���Ұ� x�� ȸ������, y�� ȸ������, z�� ȸ������ �� �ǵ��� �־���Ѵ�.
	//	���Ȱ����� ������ �ȵ�
	//	�ι�° ���ڴ� �����ӵ��� ������̴�. ���ڰ� Ŭ���� �����Ǵ� �ӵ��� ��������.
	bool SmoothRotate(D3DXVECTOR3 target, float speedMultiple = 1.0f);

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	��ü�� ��ǥ�������� �ε巴�� ȸ����Ű�� �Լ��̴�.
	//	��ü�� ��ġ�� ���ڷ� ������ x, y, z�ǰ����� ���͸� ����� �����Ѵ�.
	//	��ǥ������ ���ڷ� ������ x�� ȸ������, y�� ȸ������, z�� ȸ������ �� �ǵ��� �־���Ѵ�.
	//	���Ȱ����� ������ �ȵ�
	//	�ι�° ���ڴ� �����ӵ��� ������̴�. ���ڰ� Ŭ���� �����Ǵ� �ӵ��� ��������.
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
	//	�� �Լ��� �ڽ�(����) ���� GameObject�� �߰��ϴ� �Լ��̴�.
	//	isUpdate���ڴ� ���� �ڽ����� �߰��Ϸ��� GameObject�� ������Ʈ �� �������� �����̸�
	//	Default���� true�̹Ƿ� ���������� �⺻������ true�� ����
	//	false�� ������� �θ�(����) ��尡 ������Ʈ �� �� ������Ʈ ���� �ʴ´�.
	void PushChildObject(EVGameObject* gameObject, std::string tag, bool isUpdate = true);

	//************************************<Description>***********************************************
	//	�� �Լ��� �ڽ�(����) ���� �߰��� GameObject�� �ٽ� �ֻ����� ���� �Լ��̴�.
	//	isErase���ڴ� �ڽ��� ���� �� �޸𸮿��� ����������� �����̸�
	//	Default���� true�̹Ƿ� ���������� GameObject�� ���� �� �޸𸮻󿡼� �����.
	//	false�� ������� �ֻ����� ��ġ�ϰ� �ȴ�.
	void PopChildObject(std::string tag, bool isErase = true);

	EVGameObject* FindChildObject(std::string tag);

public:

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ��ȯ����� �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXMATRIX transformMatrix�� ������ GameObject�� ��ȯ����� ���� �����Ѵ�.
	void TransformMatrix(D3DXMATRIX transformMatrix)	{ _transformMatrix = transformMatrix; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ũ�⸦ �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXVECTOR3 scale�� ������ GameObject�� ũ�� ���� �����Ѵ�.
	void Scale(D3DXVECTOR3 scale)						{ _scale = scale; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ��ġ���� �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXVECTOR3 position�� ���� GameObject�� ��ġ���� �����Ѵ�.
	void Position(D3DXVECTOR3 position)					{ _position = position; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ũ�Ⱑ ���� �� ������ �Ǵ� ���� �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXVECTOR3 scalingCenter�� ���� GameObject�� ũ�⺯ȯ�߽ɰ��� �����Ѵ�.
	void ScalingCenter(D3DXVECTOR3 scalingCenter)		{ _scalingCenter = scalingCenter; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ȸ���� �� �߽��� �Ǵ� ���� �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXVECTOR3 rotationCenter�� ���� GameObject�� ȸ���߽ɰ��� �����Ѵ�.
	void RotationCenter(D3DXVECTOR3 rotationCenter)		{ _rotationCenter = rotationCenter; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ������Ʈ ���θ� �����ϴ� �Լ��̴�.
	void SetUpdate(bool isUpdate)						{ _update = isUpdate; }

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ũ�⸦ �����ϴ� �Լ��̴�.
	//	������ ���ڴ� x��, y��, z���� ũ�⺯ȯ���̴�.
	void Scale(X x, Y y, Z z)
	{
		_scale.x = static_cast<float>(x);
		_scale.y = static_cast<float>(y);
		_scale.z = static_cast<float>(z);
	}

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ũ�Ⱑ ���� �� ������ �Ǵ� ���� �����ϴ� �Լ��̴�.
	//	������ ���ڴ� x��, y��, z���� ũ�⺯ȯ�߽����� ��ġ���̴�.
	void ScalingCenter(X x, Y y, Z z)
	{
		_scalingCenter.x = static_cast<float>(x);
		_scalingCenter.y = static_cast<float>(y);
		_scalingCenter.z = static_cast<float>(z);
	}

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ȸ���� �� �߽��� �Ǵ� ���� �����ϴ� �Լ��̴�.
	//	������ ���ڴ� x��, y��, z���� ȸ���߽����� ��ġ��
	void RotationCenter(X x, Y y, Z z)
	{
		_rotationCenter.x = static_cast<float>(x);
		_rotationCenter.y = static_cast<float>(y);
		_rotationCenter.z = static_cast<float>(z);
	}

	template<typename X, typename Y, typename Z>
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ��ġ���� �����ϴ� �Լ��̴�.
	//	������ ���ڴ� x��, y��, z���� ��ġ���̴�.
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
	//	�� �Լ��� GameObject�� ��ȯ����� ��ȯ�ϴ� �Լ��̴�.
	D3DXMATRIX  TransformMatrix()	{ return _transformMatrix; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ũ�Ⱚ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR3
	D3DXVECTOR3 Scale()				{ return _scale; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� x�� ũ�Ⱚ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScaleX()			{ return _scale.x; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� y�� ũ�Ⱚ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScaleY()			{ return _scale.y; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� z�� ũ�Ⱚ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScaleZ()			{ return _scale.z; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ȸ������ ���Ϸ� ������ ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR3
	D3DXVECTOR3 EulerRotation()		{ return _eulerAngle; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� x�� ȸ������ ���Ϸ� ������ ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		EulerRotationX()	{ return _eulerAngle.x; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� y�� ȸ������ ���Ϸ� ������ ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		EulerRotationY()	{ return _eulerAngle.y; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� z�� ȸ������ ���Ϸ� ������ ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		EulerRotationZ()	{ return _eulerAngle.z; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ��ġ���� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR3
	D3DXVECTOR3 Position()			{ return _position; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject��  x�� ��ġ���� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		PositionX()			{ return _position.x; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� y�� ��ġ���� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		PositionY()			{ return _position.y; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� z�� ��ġ���� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		PositionZ()			{ return _position.z; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ũ�⺯ȯ�߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR3
	D3DXVECTOR3 ScalingCenter()		{ return _scalingCenter; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� x�� ũ�⺯ȯ�߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScalingCenterX()	{ return _scalingCenter.x; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� y�� ũ�⺯ȯ�߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScalingCenterY()	{ return _scalingCenter.y; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� z�� ũ�⺯ȯ�߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScalingCenterZ()	{ return _scalingCenter.z; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ȸ���߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR3
	D3DXVECTOR3 RotationCenter()	{ return _rotationCenter; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� x�� ȸ���߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		RotationCenterX()	{ return _rotationCenter.x; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� y�� ȸ���߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		RotationCenterY()	{ return _rotationCenter.y; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� z�� ȸ���߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		RotationCenterZ()	{ return _rotationCenter.z; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ���� ��ǥ���� Z�� ������ ��Ÿ���� ���͸� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR3
	D3DXVECTOR3	Forward()			{ return _forward; }
	
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ���� ��ǥ���� X�� ������ ��Ÿ���� ���͸� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR3
	D3DXVECTOR3 Right()				{ return _right; }
	
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ���� ��ǥ���� Y�� ������ ��Ÿ���� ���͸� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR3
	D3DXVECTOR3 Up()				{ return _up; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject�� ������Ʈ ���θ� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : bool
	bool		IsUpdate()			{ return _update; }

	//************************************<Description>***********************************************
	//	�� �Լ��� ����GameObject�� �θ��� �����͸� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : EVGameObject
	EVGameObject* Parent()			{ return _parent; }

	D3DXQUATERNION Rotation()		{ return _quaternionAngle; }

	std::string		Tag()			{ return _tag; }

};

#endif