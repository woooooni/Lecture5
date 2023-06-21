#include "stdafx.h"
#include "..\Header\Terrain.h"


CTerrain::CTerrain(LPDIRECT3DDEVICE9 _pDevice)
	: CGameObject(_pDevice)
{
}

CTerrain::CTerrain(const CTerrain & rhs)
	: CGameObject(rhs)
{
}

CTerrain::~CTerrain()
{
}

HRESULT CTerrain::Add_Component(void)
{
	return S_OK;
}

CTerrain * CTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CTerrain* pInstance = new CTerrain(pGraphicDev);
	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Terrain Create Failed");
		return nullptr;
	}
	return pInstance;
}

void CTerrain::Free()
{
	__super::Free();
}

