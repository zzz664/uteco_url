#include "EvolutionSkinningModel.h"
#include "EvolutionCore.h"
#include "EvolutionEffectManager.h"
#include "EvolutionInput.h"
#include "EvolutionTime.h"

EVSkinningModel::EVSkinningModel(std::string path)
{
	EVAnimationHierarchy hierarchy;

	HRESULT hr;
	hr = D3DXLoadMeshHierarchyFromXA(
		path.c_str(), 
		D3DXMESH_32BIT | D3DXMESH_MANAGED,
		EVSystem->DirectDevice(), 
		&hierarchy, 
		0,
		&_root, 
		&_animationCtrl);


	D3DXFRAME* pFrame = FindNodeWithMesh(_root);
	D3DXMESHCONTAINER* pMeshContainer = pFrame->pMeshContainer;

	_skinInfo = pMeshContainer->pSkinInfo;
	_skinInfo->AddRef();


	_numBones = pMeshContainer->pSkinInfo->GetNumBones();
	_finalTransforms.resize(_numBones);
	_combinedTransforms.resize(_numBones, 0);


	BuildSkinningModel(pMeshContainer->MeshData.pMesh);
	BuildCombinedTransform();
	BuildMaterial(pMeshContainer);
}

EVSkinningModel::~EVSkinningModel() 
{
	if (_root) 
	{
		EVAnimationHierarchy hierarchy;
		D3DXFrameDestroy(_root, &hierarchy);

		_root = NULL;
	}

	if (_skinnedMesh)
	{
		_skinnedMesh->Release();
	}

	if (_skinInfo)
	{
		_skinInfo->Release();
	}

	if (_animationCtrl)
	{
		_animationCtrl->Release();
	}
}

void EVSkinningModel::Update() 
{
	EVGameObject::Update();

	_animationCtrl->AdvanceTime(EVTime->DeltaTime(), NULL);

	D3DXMATRIX identity;
	D3DXMatrixIdentity(&identity);
	CombineTransforms(static_cast<ANIMATIONFRAME*>(_root), identity);

	D3DXMATRIX offsetTemp, combinedTemp;

	for (UINT i = 0; i < _numBones; ++i) 
	{
		offsetTemp = *_skinInfo->GetBoneOffsetMatrix(i);
		combinedTemp = *_combinedTransforms[i];
		_finalTransforms[i] = offsetTemp * combinedTemp;
	}

	_diffuseSkinning->Shader()->SetMatrixArray("finalTransforms", &_finalTransforms[0], _finalTransforms.size());
}

void EVSkinningModel::Render() 
{
	EVGameObject::Render();

	_diffuseSkinning->Shader()->SetTechnique("DiffuseSkinningTexture");

	UINT numPasses = 0;
	_diffuseSkinning->Start(&numPasses);

	for (UINT i = 0; i < numPasses; ++i) 
	{
		_diffuseSkinning->Shader()->BeginPass(i);
		{
			_skinnedMesh->DrawSubset(0);
		}
		_diffuseSkinning->Shader()->EndPass();
	}
	_diffuseSkinning->End();
}

D3DXFRAME* EVSkinningModel::FindNodeWithMesh(D3DXFRAME* pFrame) 
{
	if (pFrame->pMeshContainer)
	{
		if (pFrame->pMeshContainer->MeshData.pMesh != 0)
		{
			return pFrame;
		}
	}

	D3DXFRAME* p = 0;

	if (pFrame->pFrameSibling)
	{
		if (p = FindNodeWithMesh(pFrame->pFrameSibling))
		{
			return p;
		}
	}

	if (pFrame->pFrameFirstChild)
	{
		if (p = FindNodeWithMesh(pFrame->pFrameFirstChild))
		{
			return p;
		}
	}

	return 0;
}

void EVSkinningModel::BuildSkinningModel(ID3DXMesh* pMesh) 
{
	DWORD        numBoneComboEntries = 0;
	ID3DXBuffer* boneComboTable = 0;

	_skinInfo->ConvertToIndexedBlendedMesh(
		pMesh,
		D3DXMESH_MANAGED | D3DXMESH_WRITEONLY,
		EVSkinningModel::MAX_NUM_BONES_SUPPORTED,
		NULL,
		NULL,
		NULL,
		NULL,
		&_maxVertInfluences,
		&numBoneComboEntries,
		&boneComboTable,
		&_skinnedMesh);

	if (boneComboTable)
	{
		boneComboTable->Release();
	}
}

void EVSkinningModel::BuildMaterial(D3DXMESHCONTAINER* pMeshContainer) 
{
	D3DXMATERIAL* mtrls = pMeshContainer->pMaterials;
	DWORD numMtrls = pMeshContainer->NumMaterials;

	if (mtrls[0].pTextureFilename) 
	{
		IDirect3DTexture9* tex = 0;

		D3DXCreateTextureFromFileA(EVSystem->DirectDevice(), mtrls[0].pTextureFilename, &tex);
		
		_diffuseSkinning = new EVDiffuseSkinning(tex);

		if (tex)
		{
			tex->Release();
		}
	}
}

void EVSkinningModel::BuildCombinedTransform() 
{
	for (UINT i = 0; i < _numBones; ++i) 
	{
		const char* boneName = _skinInfo->GetBoneName(i);
		D3DXFRAME* frame = D3DXFrameFind(_root, boneName);

		if (frame) 
		{
			ANIMATIONFRAME* pAnimationFrame = static_cast<ANIMATIONFRAME*>(frame);
			_combinedTransforms[i] = &pAnimationFrame->combinedTransform;
		}
	}
}

void EVSkinningModel::CombineTransforms(ANIMATIONFRAME* frame, D3DXMATRIX& matrix) 
{
	D3DXMATRIX& L = frame->TransformationMatrix;
	D3DXMATRIX& C = frame->combinedTransform;

	C = L * matrix;

	ANIMATIONFRAME* sibling = (ANIMATIONFRAME*)frame->pFrameSibling;
	ANIMATIONFRAME* firstChild = (ANIMATIONFRAME*)frame->pFrameFirstChild;

	if (sibling)
	{
		CombineTransforms(sibling, matrix);
	}

	if (firstChild)
	{
		CombineTransforms(firstChild, C);
	}
}