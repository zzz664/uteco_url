#ifndef _EVOLUTIONANIMATIONHIERARCHY_H_
#define _EVOLUTIONANIMATIONHIERARCHY_H_

#include <d3d9.h>
#include <d3dx9.h>

class EVAnimationHierarchy : public ID3DXAllocateHierarchy
{
	HRESULT STDMETHODCALLTYPE CreateFrame(PCSTR Name, D3DXFRAME** ppNewFrame);

	HRESULT STDMETHODCALLTYPE CreateMeshContainer(
		PCSTR Name,
		const D3DXMESHDATA* pMeshData,
		const D3DXMATERIAL* pMaterials,
		const D3DXEFFECTINSTANCE* pEffectInstances,
		DWORD NumMaterials,
		const DWORD *pAdjacency,
		ID3DXSkinInfo* pSkinInfo,
		D3DXMESHCONTAINER** ppNewMeshContainer);

	HRESULT STDMETHODCALLTYPE DestroyFrame(D3DXFRAME* pFrameToFree);

	HRESULT STDMETHODCALLTYPE DestroyMeshContainer(D3DXMESHCONTAINER* pMeshContainerBase);
};

#endif