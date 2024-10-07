#ifndef _SHADER_H_
#define _SHADER_H_

#include <d3dx9.h>
#include <string>

using namespace std;

class Shader
{
protected:

	string			path;
	LPD3DXEFFECT	shader;

public:

	Shader();
	virtual ~Shader();

	virtual void Update();

	virtual void Start(UINT* numPasses);
	virtual void End();

public:

	ID3DXEffect*	GetShader();

	string			GetPath();

};

#endif 