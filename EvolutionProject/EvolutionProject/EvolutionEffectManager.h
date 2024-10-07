#ifndef _EVOLUTIONEFFECT_H_
#define _EVOLUTIONEFFECT_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <list>
#include <string>

#define EVEffectManager EvolutionEffectManager::GetInstance()

struct EffectTable {
	std::string						name;
	LPDIRECT3DVERTEXDECLARATION9	pDecl;
	LPD3DXEFFECT					pEffect;
};

class EvolutionEffectManager
{

private:

	std::list<EffectTable*> m_effectTable;

private:
	EvolutionEffectManager();

public:
	~EvolutionEffectManager();

	static EvolutionEffectManager* GetInstance();

	//************************************<Description>***********************************************
	//	이 함수는 이펙트쉐이더 객체를 만들고 추가하는 함수이다.
	//	첫번째 인자는 이펙트쉐이더의 경로이고 두번째 인자는 정점정보이다.
	void Add(std::string path, DWORD fvf);

	//************************************<Description>***********************************************
	//	이 함수는 이펙트쉐이더 객체를 가져오는 역할을 하는 함수이다.
	//	인자로 들어온 경로의 이펙트쉐이더를 반환한다.
	EffectTable* Get(std::string name);

	void Release();
};

#endif