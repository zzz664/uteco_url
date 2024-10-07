#ifndef _EVOLUTIONTEXTUREMANAGER_H_
#define _EVOLUTIONTEXTUREMANAGER_H_

#include <d3dx9.h>

#include <map>
#include <string>

#define EVTextureManager EvolutionTextureManager::GetInstance()

class EvolutionTextureManager 
{

private:

	typedef std::map<std::string, LPDIRECT3DTEXTURE9> TEXTURE;
	TEXTURE m_mapTexture;

private:

	EvolutionTextureManager();

public:

	~EvolutionTextureManager();

	static EvolutionTextureManager* GetInstance();

	//************************************<Description>***********************************************
	//	�� �Լ��� ���Ϸκ��� �ؽ��� ��ü�� �����ϴ� �Լ��̴�.
	//	���ڷ� ���� ����� ���Ϸκ��� �ؽ��� ��ü�� �����ϰ� ��ȯ�Ѵ�.
	LPDIRECT3DTEXTURE9 LoadTextureFromFile(std::string path);

	void Release();

};

#endif