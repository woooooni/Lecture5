#include "stdafx.h"
#include "..\Header\BackGround.h"

#include "Export_Function.h"

CBackGround::CBackGround(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev)
{

}

CBackGround::CBackGround(const CBackGround& rhs)
	: Engine::CGameObject(rhs)
{

}

CBackGround::~CBackGround()
{
}

HRESULT CBackGround::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	return S_OK;
}

Engine::_int CBackGround::Update_Object(const _float& fTimeDelta)
{
	return __super::Update_Object(fTimeDelta);
}

void CBackGround::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CBackGround::Render_Object(void)
{
	// m_pGraphicDev->SetTransform(D3DTS_WORLD, ? );

	m_pBufferCom->Render_Buffer();

	__super::Render_Object();
}

HRESULT CBackGround::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

/*	pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(Engine::Clone_Proto(L"Proto_TriCol"));*/
	pComponent = m_pBufferCom = dynamic_cast<CRcCol*>(Engine::Clone_Proto(L"Proto_RcCol"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);

	return S_OK;
}

void CBackGround::Free()
{
	__super::Free();
}

CBackGround* CBackGround::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CBackGround*	pInstance = new CBackGround(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("BackGround Create Failed");
		return nullptr;
	}

	return pInstance;
}
