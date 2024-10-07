#ifndef _EVOLUTIONSHADER_H_
#define _EVOLUTIONSHADER_H_

#include <d3dx9.h>
#include <string>

#include "EvolutionGameObject.h"

class EVShader : public EVGameObject
{

protected:

	std::string		_path;
	ID3DXEffect*	_shader;

public:

	EVShader();
	virtual ~EVShader();

	virtual void Update();

	void Start(UINT* numPasses);
	void End();

public:

	ID3DXEffect* Shader();

	std::string Path();


};

#endif