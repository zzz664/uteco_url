#include "EvolutionAnimationModel.h"
#include "EvolutionInput.h"
#include "EvolutionCore.h"

EVAnimationModel::EVAnimationModel(std::string path) : EVSkinningModel(path)
{
	_currentTrack = 0;
	_newTrack = 0;
}

EVAnimationModel::~EVAnimationModel()
{

}

void EVAnimationModel::Update()
{
	EVSkinningModel::Update();
}

void EVAnimationModel::Render()
{
	EVSkinningModel::Render();
}

void EVAnimationModel::ChangeAnimation(int index)
{
	ID3DXAnimationSet* animationSet;

	_animationCtrl->GetAnimationSet(index, &animationSet);
	_animationCtrl->SetTrackAnimationSet(0, animationSet);
}

void EVAnimationModel::CrossFade(int index, float speed, bool resetTrack, float transitionTime)
{
	ID3DXAnimationSet* animationSet;

	_newTrack = (_currentTrack == 0 ? 1 : 0);

	_animationCtrl->GetTrackAnimationSet(_currentTrack, &_currentAnimationSet);
	_animationCtrl->GetAnimationSet(index, &animationSet);

	if (strcmp(animationSet->GetName(), _currentAnimationSet->GetName()) == 0)
	{
		return;
	}

	if (resetTrack)
	{
		_animationCtrl->SetTrackPosition(_newTrack, 0.0);
	}

	_animationCtrl->SetTrackAnimationSet(_newTrack, animationSet);

	_animationCtrl->UnkeyAllTrackEvents(_currentTrack);
	_animationCtrl->UnkeyAllTrackEvents(_newTrack);

	_animationCtrl->KeyTrackEnable(_currentTrack, false, EVTime->CurrentTime() + transitionTime);
	_animationCtrl->KeyTrackSpeed(_currentTrack, 0.0f, EVTime->CurrentTime(), transitionTime, D3DXTRANSITION_LINEAR);
	_animationCtrl->KeyTrackWeight(_currentTrack, 0.0f, EVTime->CurrentTime(), transitionTime, D3DXTRANSITION_LINEAR);

	_animationCtrl->SetTrackEnable(_newTrack, true);
	_animationCtrl->KeyTrackSpeed(_newTrack, speed, EVTime->CurrentTime(), transitionTime, D3DXTRANSITION_LINEAR);
	_animationCtrl->KeyTrackWeight(_newTrack, 1.0f, EVTime->CurrentTime(), transitionTime, D3DXTRANSITION_LINEAR);

	_currentTrack = _newTrack;
}