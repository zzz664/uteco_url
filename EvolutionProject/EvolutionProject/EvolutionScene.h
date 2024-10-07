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
	//	이 함수는 씬이 게임오브젝트를 관리하도록 등록해주는 함수이다.
	void PushGameObject(EVGameObject* gameObject, std::string tag, bool isUpdate = true);

	//************************************<Description>***********************************************
	//	이 함수는 씬이 게임오브젝트를 관리하도록 등록해주는 함수이다.
	void PushGameObject2D(EVGameObject2D* gameObject, std::string tag, bool isUpdate = true);

	//************************************<Description>***********************************************
	//	이 함수는 씬으로부터 관리되는 게임오브젝트를 꺼내는 함수이다.
	void PopGameObject(std::string tag, bool isErase = true);

	//************************************<Description>***********************************************
	//	이 함수는 씬으로부터 관리되는 게임오브젝트를 꺼내는 함수이다.
	void PopGameObject2D(std::string tag, bool isErase = true);

	EVGameObject* FindGameObject(std::string tag);
	EVGameObject2D* FindGameObject2D(std::string tag);

	EVGameObject* FindChildObject(EVGameObject* gameObject, std::string tag);
	EVGameObject2D* FindChildObject2D(EVGameObject2D* gameObject, std::string tag);

};

#endif