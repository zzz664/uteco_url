#include "EvolutionEffectManager.h"
#include "EvolutionCore.h"

EvolutionEffectManager::EvolutionEffectManager() 
{
}

EvolutionEffectManager::~EvolutionEffectManager() 
{
}

EvolutionEffectManager* EvolutionEffectManager::GetInstance() 
{
	static EvolutionEffectManager Instance;
	return &Instance;
}
void EvolutionEffectManager::Add(std::string name, DWORD fvf) 
{
	D3DVERTEXELEMENT9	decl[MAX_FVF_DECL_SIZE];

	if (Get(name))
	{
		return;
	}

	EffectTable* p = new EffectTable;
	p->name = name;

	D3DXDeclaratorFromFVF(fvf, decl);
	EVSystem->DirectDevice()->CreateVertexDeclaration(decl, &p->pDecl);

	D3DXCreateEffectFromFileA(EVSystem->DirectDevice(), name.c_str(), NULL, NULL, 0, NULL, &p->pEffect, NULL);

	m_effectTable.push_back(p);
}
EffectTable* EvolutionEffectManager::Get(std::string name) 
{
	std::list<EffectTable*>::iterator it;

	for (it = m_effectTable.begin(); it != m_effectTable.end(); it++)
	{
		if ((*it)->name == name)
		{
			return *it;
		}
	}

	return NULL;
}
void EvolutionEffectManager::Release() 
{
	std::list<EffectTable*>::iterator it;

	for (it = m_effectTable.begin(); it != m_effectTable.end(); ++it) 
	{
		if ((*it)->pDecl)
		{
			(*it)->pDecl->Release();
			(*it)->pDecl = NULL;
		}

		if ((*it)->pEffect)
		{
			(*it)->pEffect->Release();
			(*it)->pEffect = NULL;
		}
	}

	for (it = m_effectTable.begin(); it != m_effectTable.end(); ++it) 
	{
		if ((*it))
		{
			delete (*it);
		}
	}

	m_effectTable.clear();
}