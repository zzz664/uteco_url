#ifndef _EVOLUTIONSCENE_H_
#define _EVOLUTIONSCENE_H_

#include "EvolutionGameObject.h"
#include "EvolutionGameObject2D.h"

class EVScene 
{
protected:
	list<EVGameObject*>		_gameObjects;
	list<EVGameObject2D*>	_gameObjects2D;

public:

	EVScene();
	virtual ~EVScene();

	virtual void Update();
	virtual void Render() = 0;

public:

	//************************************<Description>***********************************************
	//	�� �Լ��� ���� ���ӿ�����Ʈ�� �����ϵ��� ������ִ� �Լ��̴�.
	void PushGameObject(EVGameObject* gameObject, std::string tag, bool isUpdate = true);

	//************************************<Description>***********************************************
	//	�� �Լ��� ���� ���ӿ�����Ʈ�� �����ϵ��� ������ִ� �Լ��̴�.
	void PushGameObject2D(EVGameObject2D* gameObject, std::string tag, bool isUpdate = true);

	//************************************<Description>***********************************************
	//	�� �Լ��� �����κ��� �����Ǵ� ���ӿ�����Ʈ�� ������ �Լ��̴�.
	void PopGameObject(std::string tag, bool isErase = true);

	//************************************<Description>***********************************************
	//	�� �Լ��� �����κ��� �����Ǵ� ���ӿ�����Ʈ�� ������ �Լ��̴�.
	void PopGameObject2D(std::string tag, bool isErase = true);

	EVGameObject* FindGameObject(std::string tag);
	EVGameObject2D* FindGameObject2D(std::string tag);

	EVGameObject* FindChildObject(EVGameObject* gameObject, std::string tag);
	EVGameObject2D* FindChildObject2D(EVGameObject2D* gameObject, std::string tag);

};

#endif