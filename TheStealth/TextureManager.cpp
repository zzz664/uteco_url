#include "TextureManager.h"
#include "DirectX9.h"

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
	TEXTUREMAP::iterator it;

	for (it = textures.begin(); it != textures.end(); ++it)
	{
		it->second->Release();
	}
}

TextureManager* TextureManager::GetInstance()
{
	static TextureManager instance;
	return &instance;
}

LPDIRECT3DTEXTURE9 TextureManager::LoadTextureFromFile(string path)
{
	if (textures[path] != NULL)
		return textures[path];

	D3DXCreateTextureFromFileExA(
		DirectX9->GetDevice(),
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
		&textures[path]);

	return textures[path];
}