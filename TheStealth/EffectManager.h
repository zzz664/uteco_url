#ifndef _EFFECTMANAGER_H_
#define _EFFECTMANAGER_H_

#include <d3d9.h>
#include <d3dx9.h>
#include <list>
#include <string>

#define EFFECT EffectManager::GetInstance()

struct EffectTable
{
	std::string						name;
	LPDIRECT3DVERTEXDECLARATION9	pDecl;
	LPD3DXEFFECT					pShader;
};

class EffectManager 
{

private:

	std::list<EffectTable*> effectTable;

	EffectManager();

public:

	~EffectManager();

	static EffectManager* GetInstance();

	void Add(std::string path, DWORD fvf);
	EffectTable* Get(std::string effectName);
};

#endif