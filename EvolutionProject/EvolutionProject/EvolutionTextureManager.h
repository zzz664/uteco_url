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
	//	이 함수는 파일로부터 텍스쳐 객체를 생성하는 함수이다.
	//	인자로 들어온 경로의 파일로부터 텍스쳐 객체를 생성하고 반환한다.
	LPDIRECT3DTEXTURE9 LoadTextureFromFile(std::string path);

	void Release();

};

#endif