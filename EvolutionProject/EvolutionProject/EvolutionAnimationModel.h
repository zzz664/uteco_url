#ifndef _EVOLUTIONANIMATIONMODEL_H_
#define _EVOLUTIONANIMATIONMODEL_H_

#include "EvolutionSkinningModel.h"

class EVAnimationModel : public EVSkinningModel
{

private:

	DWORD						_currentTrack;
	DWORD						_newTrack;
	ID3DXAnimationSet*			_currentAnimationSet;

public:

	EVAnimationModel(std::string path);
	~EVAnimationModel();

	void Update();
	void Render();

public:

	void ChangeAnimation(int index);
	void CrossFade(int index, float speed, bool resetTrack = true, float transitionTime = 0.125f);

public:

	DWORD CurrentTrack() { return _newTrack; }
};

#endif