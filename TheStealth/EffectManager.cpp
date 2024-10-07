#include "EffectManager.h"
#include "DirectX9.h"

EffectManager::EffectManager() 
{
}

EffectManager::~EffectManager() 
{
	std::list<EffectTable*>::iterator it;
	for (it = effectTable.begin(); it != effectTable.end(); ++it)
	{
		(*it)->pDecl->Release();
		(*it)->pDecl = nullptr;

		(*it)->pShader->Release();
		(*it)->pShader = 0;
	}

	for (it = effectTable.begin(); it != effectTable.end(); ++it)
	{
		delete (*it);
	}

	effectTable.clear();
}

EffectManager* EffectManager::GetInstance() 
{
	static EffectManager Instance;
	return &Instance;
}

void EffectManager::Add(std::string name, DWORD fvf) 
{
	D3DVERTEXELEMENT9	decl[MAX_FVF_DECL_SIZE];

	if (Get(name))
		return;

	EffectTable* p = new EffectTable;
	p->name = name;

	D3DXDeclaratorFromFVF(fvf, decl);
	DirectX9->GetDevice()->CreateVertexDeclaration(decl, &p->pDecl);

	D3DXCreateEffectFromFileA(DirectX9->GetDevice(), name.c_str(), NULL, NULL, 0, NULL, &p->pShader, NULL);

	effectTable.push_back(p);
}

EffectTable* EffectManager::Get(std::string effectName) 
{
	std::list<EffectTable*>::iterator it;
	for (it = effectTable.begin(); it != effectTable.end(); it++)
	{
		if ((*it)->name == effectName)
			return *it;
	}
	return 0;
}