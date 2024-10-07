#ifndef _TEXTUREMANAGER_H_
#define _TEXTUREMANAGER_H_

#include <d3dx9.h>

#include <map>
#include <string>

using namespace std;

#define TEXTURE TextureManager::GetInstance()

class TextureManager
{

private:

	typedef std::map<string, LPDIRECT3DTEXTURE9> TEXTUREMAP;
	TEXTUREMAP textures;

	TextureManager();

public:

	~TextureManager();

	static TextureManager* GetInstance();

	LPDIRECT3DTEXTURE9 LoadTextureFromFile(string path);

};

#endif