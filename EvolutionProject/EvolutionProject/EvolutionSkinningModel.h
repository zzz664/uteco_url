#ifndef _EVOLUTIONSKINNINGMODEL_H_
#define _EVOLUTIONSKINNINGMODEL_H_

#include "EvolutionGameObject.h"
#include "EvolutionAnimationHierarchy.h"
#include "EvolutionDiffuseSkinning.h"

#include <vector>

struct ANIMATIONFRAME : public D3DXFRAME 
{
	D3DXMATRIX combinedTransform;
};

class EVSkinningModel : public EVGameObject
{

protected:

	ID3DXMesh*					_skinnedMesh;
	IDirect3DTexture9*			_tex;
	D3DXFRAME*					_root;
	DWORD						_maxVertInfluences;
	DWORD						_numBones;
	ID3DXSkinInfo*				_skinInfo;
	ID3DXAnimationController*	_animationCtrl;

	std::vector<D3DXMATRIX>		_finalTransforms;
	std::vector<D3DXMATRIX*>	_combinedTransforms;

	static const int MAX_NUM_BONES_SUPPORTED = 35;

	EVDiffuseSkinning*			_diffuseSkinning;

public:

	EVSkinningModel(std::string path);
	virtual ~EVSkinningModel();

	virtual void Update();
	virtual void Render();

protected:

	D3DXFRAME* FindNodeWithMesh(D3DXFRAME* frame);
	void BuildSkinningModel(ID3DXMesh* mesh);
	void BuildMaterial(D3DXMESHCONTAINER* meshContainer);
	void BuildCombinedTransform();
	void CombineTransforms(ANIMATIONFRAME* frame, D3DXMATRIX& matrix);

	EVSkinningModel(const EVSkinningModel& rhs);
	EVSkinningModel& operator=(const EVSkinningModel& rhs);

public:

	D3DXFRAME*					Root()					{ return _root; }
	ID3DXAnimationController*	AnimationController()	{ return _animationCtrl; }
	ID3DXSkinInfo*				SkinInfo()				{ return _skinInfo; }

};

#endif