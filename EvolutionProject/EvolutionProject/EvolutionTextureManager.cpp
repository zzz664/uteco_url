#include "EvolutionTextureManager.h"
#include "EvolutionCore.h"

EvolutionTextureManager::EvolutionTextureManager() 
{
}

EvolutionTextureManager::~EvolutionTextureManager() 
{
}

EvolutionTextureManager* EvolutionTextureManager::GetInstance() 
{
	static EvolutionTextureManager instance;
	return &instance;
}

LPDIRECT3DTEXTURE9 EvolutionTextureManager::LoadTextureFromFile(std::string path)
{
	if (m_mapTexture[path] != NULL)
		return m_mapTexture[path];

	D3DXCreateTextureFromFileExA(
		EVSystem->DirectDevice(),
		path.c_str(),
		D3DX_DEFAULT_NONPOW2,
		D3DX_DEFAULT_NONPOW2,
		1,
		0,
		D3DFMT_UNKNOWN,
		D3DPOOL_MANAGED,
		D3DX_DEFAULT,
		D3DX_DEFAULT,
		NULL,
		NULL,
		NULL,
		&m_mapTexture[path]);

	return m_mapTexture[path];
}
void EvolutionTextureManager::Release()
{
	TEXTURE::iterator it;

	for (it = m_mapTexture.begin(); it != m_mapTexture.end(); ++it)
	{
		it->second->Release();
	}
}