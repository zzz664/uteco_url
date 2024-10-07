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
	//	EVGameObject2DŬ������ �������̴�.
	EVGameObject2D();

	//************************************<Description>***********************************************
	//	 EVGameObject2DŬ������ �Ҹ����̴�.
	virtual ~EVGameObject2D();

	//************************************<Description>***********************************************
	//	�� �����Ӹ��� ȣ��Ǵ� �Լ��� �ǽð����� �ٲ�� ������ ó���Ѵ�.
	//	EVGameObject2DŬ������ Update�Լ��� �ڽ�(����) ������ Update�Լ��� ȣ���Ѵ�.
	virtual void Update();

	//************************************<Description>***********************************************
	//	�� ������ ���� ȣ��Ǵ� �Լ��� GameObject2D�� �̵�, ȸ��, ũ�� ��ȯ�� �����Ѵ�.
	//	���� �θ�(����) ��尡 �����Ѵٸ� �ڽ��� ��ȯ��Ŀ� �θ��� ��ȯ����� �����ؼ� ���Ѵ�.
	virtual void Render();

public:

	//************************************<Description>***********************************************
	//	�� �Լ��� �ڽ�(����) ���� GameObject2D�� �߰��ϴ� �Լ��̴�.
	//	isUpdate���ڴ� ���� �ڽ����� �߰��Ϸ��� GameObject�� ������Ʈ �� �������� �����̸�
	//	Default���� true�̹Ƿ� ���������� �⺻������ true�� ����
	//	false�� ������� �θ�(����) ��尡 ������Ʈ �� �� ������Ʈ ���� �ʴ´�.
	void PushChildObject(EVGameObject2D* gameObject, std::string tag, bool isUpdate = true);

	//************************************<Description>***********************************************
	//	�� �Լ��� �ڽ�(����) ���� �߰��� GameObject2D�� �ٽ� �ֻ����� ���� �Լ��̴�.
	//	isErase���ڴ� �ڽ��� ���� �� �޸𸮿��� ����������� �����̸�
	//	Default���� true�̹Ƿ� ���������� GameObject�� ���� �� �޸𸮻󿡼� �����.
	//	false�� ������� �ֻ����� ��ġ�ϰ� �ȴ�.
	void PopChildObject(std::string tag, bool isErase = true);

	EVGameObject2D* FindChildObject(std::string tag);

public:

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ��ȯ����� �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXMATRIX transformMatrix�� ������ GameObject�� ��ȯ����� ���� �����Ѵ�.
	void TransformMatrix(D3DXMATRIX transformMatrix)	{ _transformMatrix = transformMatrix; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ũ�⸦ �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXVECTOR3 scale�� ������ GameObject2D�� ũ�� ���� �����Ѵ�.
	void Scale(D3DXVECTOR2 scale)						{ _scale = scale; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ������ �����ϴ� �Լ��̴�.
	//	���ڷ� ������ float rotation�� ������ GameObject2D�� ȸ�� ���� �����Ѵ�.
	void Rotation(float rotation)						{ _rotation = rotation; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ��ġ���� �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXVECTOR2 position�� ���� GameObject2D�� ��ġ���� �����Ѵ�.
	void Position(D3DXVECTOR2 position)					{ _position = position; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ũ�Ⱑ ���� �� ������ �Ǵ� ���� �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXVECTOR2 scalingCenter�� ���� GameObject2D�� ũ�⺯ȯ�߽ɰ��� �����Ѵ�.
	void ScalingCenter(D3DXVECTOR2 scalingCenter)		{ _scalingCenter = scalingCenter; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ȸ���� �� �߽��� �Ǵ� ���� �����ϴ� �Լ��̴�.
	//	���ڷ� ������ D3DXVECTOR2 rotationCenter�� ���� GameObject2D�� ȸ���߽ɰ��� �����Ѵ�.
	void RotationCenter(D3DXVECTOR2 rotationCenter)		{ _rotationCenter = rotationCenter; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ������Ʈ ���θ� �����ϴ� �Լ��̴�.
	void SetUpdate(bool isUpdate)						{ _update = isUpdate; }

	template<typename X, typename Y>
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ũ�⸦ �����ϴ� �Լ��̴�.
	//	������ ���ڴ� x��, y���� ũ�⺯ȯ���̴�.
	void Scale(X x, Y y)
	{
		_scale.x = static_cast<float>(x);
		_scale.y = static_cast<float>(y);
	}

	template<typename X>
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ������ �����ϴ� �Լ��̴�.
	//	���ڴ� ȸ�������̴�.
	void Rotation(X x)
	{
		_rotation = static_cast<float>(x);
	}

	template<typename X, typename Y>
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ũ�Ⱑ ���� �� ������ �Ǵ� ���� �����ϴ� �Լ��̴�.
	//	������ ���ڴ� x��, y���� ũ�⺯ȯ�߽����� ��ġ���̴�.
	void ScalingCenter(X x, Y y)
	{
		_scalingCenter.x = static_cast<float>(x);
		_scalingCenter.y = static_cast<float>(y);
	}

	template<typename X, typename Y>
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ȸ���� �� �߽��� �Ǵ� ���� �����ϴ� �Լ��̴�.
	//	������ ���ڴ� x��, y���� ȸ���߽����� ��ġ��
	void RotationCenter(X x, Y y)
	{
		_rotationCenter.x = static_cast<float>(x);
		_rotationCenter.y = static_cast<float>(y);
	}

	template<typename X, typename Y>
	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ��ġ���� �����ϴ� �Լ��̴�.
	//	������ ���ڴ� x��, y���� ��ġ���̴�.
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
	//	�� �Լ��� GameObject2D�� ��ȯ����� ��ȯ�ϴ� �Լ��̴�.
	D3DXMATRIX  TransformMatrix()	{ return _transformMatrix; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ũ�Ⱚ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR2
	D3DXVECTOR2 Scale()				{ return _scale; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� x�� ũ�Ⱚ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScaleX()			{ return _scale.x; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� y�� ũ�Ⱚ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScaleY()			{ return _scale.y; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ȸ������ ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		Rotation()			{ return _rotation; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ��ġ���� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR2
	D3DXVECTOR2 Position()			{ return _position; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D��  x�� ��ġ���� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		PositionX()			{ return _position.x; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� y�� ��ġ���� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		PositionY()			{ return _position.y; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ũ�⺯ȯ�߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR2
	D3DXVECTOR2 ScalingCenter()		{ return _scalingCenter; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� x�� ũ�⺯ȯ�߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScalingCenterX()	{ return _scalingCenter.x; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� y�� ũ�⺯ȯ�߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		ScalingCenterY()	{ return _scalingCenter.y; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ȸ���߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : D3DXVECTOR2
	D3DXVECTOR2 RotationCenter()	{ return _rotationCenter; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� x�� ȸ���߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		RotationCenterX()	{ return _rotationCenter.x; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� y�� ȸ���߽�����ġ�� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : float
	float		RotationCenterY()	{ return _rotationCenter.y; }

	//************************************<Description>***********************************************
	//	�� �Լ��� GameObject2D�� ������Ʈ ���θ� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : bool
	bool		IsUpdate()			{ return _update; }

	//************************************<Description>***********************************************
	//	�� �Լ��� ����GameObject2D�� �θ��� �����͸� ��ȯ�ϴ� �Լ��̴�.
	//	��ȯŸ�� : EVGameObject2D
	EVGameObject2D* Parent()		{ return _parent; }

	std::string		Tag()			{ return _tag; }

};

#endif