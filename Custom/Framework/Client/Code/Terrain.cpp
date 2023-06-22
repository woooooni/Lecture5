#include "stdafx.h"
#include "..\Header\Terrain.h"
#include "Export_Function.h"

#include "RcTerrain.h"


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



HRESULT CTerrain::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransformCom->Set_Pos(&_vec3(0.f, 0.f, 0.f));
	return S_OK;
}

_int CTerrain::Update_Object(const _float & fTimeDelta)
{
	
	_int iResult = __super::Update_Object(fTimeDelta);
	//Key_Input(fTimeDelta);
	return iResult;
}

void CTerrain::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CTerrain::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());

	m_pTextureCom->Render_Texture(0);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	m_pGraphicDev->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);
}

void CTerrain::Key_Input(const _float & fTimeDelta)
{
	//if (GetAsyncKeyState(VK_UP) & 0x8001)
	//{
	//	_vec3 vPos;
	//	m_pTransformCom->Get_Info(MATRIX_INFO::INFO_POS, &vPos);
	//	vPos.z -= 10.f * fTimeDelta;
	//	m_pTransformCom->Set_Pos(&vPos);
	//}

	//if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	//{
	//	_vec3 vPos;
	//	m_pTransformCom->Get_Info(MATRIX_INFO::INFO_POS, &vPos);
	//	vPos.z += 10.f * fTimeDelta;
	//	m_pTransformCom->Set_Pos(&vPos);
	//}

	//if (GetAsyncKeyState('Q'))
	//	m_pTransformCom->Rotation(ROT_X, D3DXToRadian(180.f * fTimeDelta));

	//if (GetAsyncKeyState('A'))
	//	m_pTransformCom->Rotation(ROT_X, D3DXToRadian(-180.f * fTimeDelta));

	//if (GetAsyncKeyState('W'))
	//	m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(180.f * fTimeDelta));

	//if (GetAsyncKeyState('S'))
	//	m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(-180.f * fTimeDelta));

	//if (GetAsyncKeyState('E'))
	//	m_pTransformCom->Rotation(ROT_Z, D3DXToRadian(180.f * fTimeDelta));

	//if (GetAsyncKeyState('D'))
	//	m_pTransformCom->Rotation(ROT_Z, D3DXToRadian(-180.f * fTimeDelta));
}

HRESULT CTerrain::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	pComponent = m_pBufferCom = dynamic_cast<CRcTerrain*>(Engine::Clone_Proto(L"Proto_RcTerrain"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pBufferCom->SetOwner(this);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);


	pComponent = m_pTextureCom = dynamic_cast<CTexture*>(Engine::Clone_Proto(L"Proto_Texture_Terrain"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pTextureCom->SetOwner(this);
	m_mapComponent[ID_STATIC].emplace(L"Com_Texture", pComponent);

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_pTransformCom->SetOwner(this);
	m_mapComponent[ID_STATIC].emplace(L"Com_Transform", pComponent);

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

