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
	//	�� �Լ��� ����Ʈ���̴� ��ü�� ����� �߰��ϴ� �Լ��̴�.
	//	ù��° ���ڴ� ����Ʈ���̴��� ����̰� �ι�° ���ڴ� ���������̴�.
	void Add(std::string path, DWORD fvf);

	//************************************<Description>***********************************************
	//	�� �Լ��� ����Ʈ���̴� ��ü�� �������� ������ �ϴ� �Լ��̴�.
	//	���ڷ� ���� ����� ����Ʈ���̴��� ��ȯ�Ѵ�.
	EffectTable* Get(std::string name);

	void Release();
};

#endif