#include "EvolutionAnimationHierarchy.h"
#include "EvolutionSkinningModel.h"

void CopyString(const char* input, char** output) 
{
	if (input) 
	{
		UINT length = (UINT)::strlen(input) + 1;

		*output = new char[length];

		strcpy(*output, input);
	}

	else 
	{
		*output = 0;
	}
}

HRESULT EVAnimationHierarchy::CreateFrame(PCSTR Name, D3DXFRAME** ppNewFrame) {
	ANIMATIONFRAME* frame = new ANIMATIONFRAME;

	if (Name)
	{
		CopyString(Name, &frame->Name);
	}

	else
	{
		CopyString("<no name>", &frame->Name);
	}

	frame->pMeshContainer = 0;
	frame->pFrameSibling = 0;
	frame->pFrameFirstChild = 0;

	D3DXMatrixIdentity(&frame->TransformationMatrix);
	D3DXMatrixIdentity(&frame->combinedTransform);

	*ppNewFrame = frame;

	return D3D_OK;
}

HRESULT EVAnimationHierarchy::CreateMeshContainer(
	PCSTR Name,
	const D3DXMESHDATA* pMeshData, 
	const D3DXMATERIAL* pMaterials,
	const D3DXEFFECTINSTANCE* pEffectInstances, 
	DWORD NumMaterials,
	const DWORD *pAdjacency, 
	ID3DXSkinInfo* pSkinInfo,
	D3DXMESHCONTAINER** ppNewMeshContainer)
{
	D3DXMESHCONTAINER* pMeshContainer = new D3DXMESHCONTAINER();

	ZeroMemory(pMeshContainer, sizeof(D3DXMESHCONTAINER));

	if (Name)
	{
		CopyString(Name, &pMeshContainer->Name);
	}

	else
	{
		CopyString("<no name>", &pMeshContainer->Name);
	}

	*ppNewMeshContainer = pMeshContainer;

	if (pSkinInfo == 0 || pMeshData->Type != D3DXMESHTYPE_MESH)
	{
		return D3D_OK;
	}

	pMeshContainer->NumMaterials = NumMaterials;
	pMeshContainer->pMaterials = new D3DXMATERIAL[NumMaterials];

	for (int i = 0; i < NumMaterials; ++i) 
	{
		D3DXMATERIAL* mtrls = pMeshContainer->pMaterials;

		mtrls[i].MatD3D = pMaterials[i].MatD3D;
		mtrls[i].MatD3D.Ambient = pMaterials[i].MatD3D.Diffuse;

		CopyString(
			pMaterials[i].pTextureFilename,
			&mtrls[i].pTextureFilename);
	}

	pMeshContainer->pAdjacency = 0;
	pMeshContainer->pEffects = 0;

	pMeshContainer->MeshData.Type = D3DXMESHTYPE_MESH;
	pMeshContainer->MeshData.pMesh = pMeshData->pMesh;
	pMeshContainer->pSkinInfo = pSkinInfo;

	pMeshData->pMesh->AddRef();
	pSkinInfo->AddRef();

	return D3D_OK;
}

HRESULT EVAnimationHierarchy::DestroyFrame(D3DXFRAME* pFrameToFree) {
	if (pFrameToFree->Name)
	{
		delete[] pFrameToFree->Name;
	}

	if (pFrameToFree)
	{
		delete pFrameToFree;
	}

	return D3D_OK;
}

HRESULT EVAnimationHierarchy::DestroyMeshContainer(D3DXMESHCONTAINER* pMeshContainerBase) {
	if (pMeshContainerBase->Name)
	{
		delete[] pMeshContainerBase->Name;
	}

	if (pMeshContainerBase->pAdjacency)
	{
		delete[] pMeshContainerBase->pAdjacency;
	}

	if (pMeshContainerBase->pEffects)
	{
		delete[] pMeshContainerBase->pEffects;
	}

	for (int i = 0; i < pMeshContainerBase->NumMaterials; ++i)
	{
		if (pMeshContainerBase->pMaterials[i].pTextureFilename)
		{
			delete[] pMeshContainerBase->pMaterials[i].pTextureFilename;
		}
	}

	if (pMeshContainerBase->pMaterials)
	{
		delete[] pMeshContainerBase->pMaterials;
	}

	if (pMeshContainerBase->MeshData.pMesh)
	{
		pMeshContainerBase->MeshData.pMesh->Release();
	}

	if (pMeshContainerBase->pSkinInfo)
	{
		pMeshContainerBase->pSkinInfo->Release();
	}

	if (pMeshContainerBase)
	{
		delete pMeshContainerBase;
	}

	return D3D_OK;
}