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

	//m_pGraphicDev->SetRenderState(D3DRS_ZENABLE, TRUE);			// Z���ۿ� ���� ���� ������ ���, ������ ������ �� ���� �����ϴ� �ɼ�
	//m_pGraphicDev->SetRenderState(D3DRS_ZWRITEENABLE, TRUE);	// Z���ۿ� �ȼ��� ���� ���� ��� �� �� ���� �����ϴ� �ɼ�

	return S_OK;
}

Engine::_int CBackGround::Update_Object(const _float& fTimeDelta)
{

	__super::Update_Object(fTimeDelta);

	Engine::Add_RenderGroup(RENDER_PRIORITY, this);

	return 0;
}

void CBackGround::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CBackGround::Render_Object(void)
{
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);
	
	//m_pGraphicDev->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);
	//m_pGraphicDev->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);

	//m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, TRUE);

	//m_pGraphicDev->SetRenderState(D3DRS_ALPHAREF, (DWORD)0x00000001);
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHAFUNC, D3DCMP_GREATER);

	m_pTextureCom->Render_Texture(0);
	m_pBufferCom->Render_Buffer();
		
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHATESTENABLE, FALSE);
	//m_pGraphicDev->SetRenderState(D3DRS_ALPHABLENDENABLE, FALSE);
}

HRESULT CBackGround::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);

	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_Texture_Logo"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Texture_Logo", pComponent);

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
