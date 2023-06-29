#include "stdafx.h"
#include "..\Header\Player.h"

#include "Export_Function.h"
#include "Bullet.h"

#include "Scene.h"
#include "Terrain.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CGameObject(pGraphicDev, OBJ_TYPE::OBJ_PLAYER)
	, m_fSpeed(5.f)
{

}
CPlayer::CPlayer(const CPlayer& rhs)
	: Engine::CGameObject(rhs)
	, m_fSpeed(rhs.m_fSpeed)
{

}
CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);

	
	m_pAnimator->Add_Animation(L"Player", L"Proto_Texture_Player");
	m_pAnimator->Play_Animation(L"Player");

	return S_OK;
}

Engine::_int CPlayer::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);

	Key_Input(fTimeDelta);
	CTerrain* pTerrain = dynamic_cast<CTerrain*>(Engine::GetCurrScene()->Get_Layer(LAYER_TYPE::ENVIRONMENT)->Find_GameObject(L"Terrain"));
	pTerrain->SetY_Terrain(this, fTimeDelta);

	return iExit;
}

void CPlayer::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
	Engine::Add_RenderGroup(RENDERID::RENDER_ALPHA, this);
}

void CPlayer::Render_Object(void)
{
	m_pGraphicDev->SetTransform(D3DTS_WORLD, m_pTransformCom->Get_WorldMatrix());
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);

	__super::Render_Object();
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
}

HRESULT CPlayer::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

/*	pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(Engine::Clone_Proto(L"Proto_TriCol"));*/
	pComponent = m_pBufferCom = dynamic_cast<CRcTex*>(Engine::Clone_Proto(L"Proto_RcTex"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetOwner(this);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetOwner(this);
	m_mapComponent[ID_STATIC].emplace(L"Com_Transform", pComponent);

	pComponent = m_pColliderCom = dynamic_cast<CBoxCollider*>(Engine::Clone_Proto(L"Proto_BoxCollider"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetOwner(this);
	m_mapComponent[ID_DYNAMIC].emplace(L"Com_BoxCollider", pComponent);

	pComponent = m_pAnimator = dynamic_cast<CAnimator*>(Engine::Clone_Proto(L"Proto_Animator"));
	pComponent->SetOwner(this);
	m_mapComponent[ID_DYNAMIC].emplace(L"Com_Animator", pComponent);

	return S_OK;
}

void CPlayer::Key_Input(const _float& fTimeDelta)
{
	m_pTransformCom->Get_Info(INFO_LOOK, &m_vDir);

	if (GetAsyncKeyState(VK_UP))
	{
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		m_pTransformCom->Move_Pos(&m_vDir, fTimeDelta, m_fSpeed);
	}

	if (GetAsyncKeyState(VK_DOWN))
	{
		D3DXVec3Normalize(&m_vDir, &m_vDir);
		m_pTransformCom->Move_Pos(&m_vDir, fTimeDelta, -m_fSpeed);
	}

	if (GetAsyncKeyState(VK_LEFT))
	{
		m_pTransformCom->RotationAxis({ 0.f, 1.f, 0.f }, D3DXToRadian(-180.f * fTimeDelta));
	}

	if (GetAsyncKeyState(VK_RIGHT))
	{
		m_pTransformCom->RotationAxis({ 0.f, 1.f, 0.f }, D3DXToRadian(180.f * fTimeDelta));
	}

	//if (GetAsyncKeyState('Q'))
	//	m_pTransformCom->Rotation(ROT_X, D3DXToRadian(180.f * fTimeDelta));

	//if (GetAsyncKeyState('A'))
	//	m_pTransformCom->Rotation(ROT_X, D3DXToRadian(-180.f * fTimeDelta));
	//
	//if (GetAsyncKeyState('W'))
	//	m_pTransformCom->RotationAxis({ 0.f, 1.f, 0.f }, D3DXToRadian(180.f * fTimeDelta));

	//if (GetAsyncKeyState('S'))
	//	m_pTransformCom->RotationAxis({ 0.f, 1.f, 0.f }, D3DXToRadian(-180.f * fTimeDelta));

	//if (GetAsyncKeyState('E'))
	//	m_pTransformCom->Rotation(ROT_Z, D3DXToRadian(180.f * fTimeDelta));

	//if (GetAsyncKeyState('D'))
	//	m_pTransformCom->Rotation(ROT_Z, D3DXToRadian(-180.f * fTimeDelta));

}

void CPlayer::Shoot()
{

}

void CPlayer::Free()
{
	__super::Free();
}

CPlayer* CPlayer::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CPlayer*	pInstance = new CPlayer(pGraphicDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pInstance;
}
