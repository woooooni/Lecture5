#include "stdafx.h"
#include "Player.h"
#include "TimerMgr.h"
#include "Export_Utility.h"
#include "Transform.h"

CPlayer::CPlayer(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
	, m_pBufferCom(nullptr)
	, m_pTransformCom(nullptr)
{
}

CPlayer::CPlayer(const CGameObject & rhs)
	: CGameObject(rhs)
{
	
}

CPlayer::~CPlayer()
{
}

HRESULT CPlayer::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CPlayer::Update_Object(const _float & fTimeDelta)
{
	Input(fTimeDelta);
	return __super::Update_Object(fTimeDelta);
}

void CPlayer::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CPlayer::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	const _matrix& matWorld = m_pTransformCom->GetWorldMat();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &matWorld);
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	__super::Render_Object();
}

HRESULT CPlayer::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	/*	pComponent = m_pBufferCom = dynamic_cast<CTriCol*>(Engine::Clone_Proto(L"Proto_TriCol"));*/
	pComponent = m_pBufferCom = dynamic_cast<Engine::CTriCol*>(Engine::Clone_Proto(L"Proto_TriCol"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_STATIC].emplace(L"Com_Buffer", pComponent);
	m_pBufferCom->SetOwner(this);


	pComponent = nullptr;
	pComponent = m_pTransformCom = dynamic_cast<Engine::CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	m_mapComponent[ID_DYNAMIC].emplace(L"Com_Transform", pComponent);
	m_pTransformCom->SetOwner(this);

	return S_OK;
}

CPlayer * CPlayer::Create(LPDIRECT3DDEVICE9 _pDev)
{
	CPlayer*	pInstance = new CPlayer(_pDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Player Create Failed");
		return nullptr;
	}

	return pInstance;
	
}

void CPlayer::Free()
{
	__super::Free();
}

void CPlayer::Input(const _float& fTimeDelta)
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		_vec3 vPos = m_pTransformCom->GetPosition();
		vPos.x -= 10.f * fTimeDelta;
		m_pTransformCom->SetPosition(vPos);
	}

	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		_vec3 vPos = m_pTransformCom->GetPosition();
		vPos.y += 10.f * fTimeDelta;
		m_pTransformCom->SetPosition(vPos);
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		_vec3 vPos = m_pTransformCom->GetPosition();
		vPos.x += 10.f * fTimeDelta;
		m_pTransformCom->SetPosition(vPos);
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		_vec3 vPos = m_pTransformCom->GetPosition();
		vPos.y -= 10.f * fTimeDelta;
		m_pTransformCom->SetPosition(vPos);
	}

	if (GetAsyncKeyState('Q') & 0x8001)
	{
		_vec3 vRot = m_pTransformCom->GetRotation();
		vRot.y -= 10.f * fTimeDelta;
		m_pTransformCom->SetRotation(vRot);
	}

	if (GetAsyncKeyState('E') & 0x8001)
	{
		_vec3 vRot = m_pTransformCom->GetRotation();
		vRot.y += 10.f * fTimeDelta;
		m_pTransformCom->SetRotation(vRot);
	}

	if (GetAsyncKeyState('W') & 0x8001)
	{
		_vec3 vRot = m_pTransformCom->GetRotation();
		vRot.x += 10.f * fTimeDelta;
		m_pTransformCom->SetRotation(vRot);
	}

	if (GetAsyncKeyState('S') & 0x8001)
	{
		_vec3 vRot = m_pTransformCom->GetRotation();
		vRot.x -= 10.f * fTimeDelta;
		m_pTransformCom->SetRotation(vRot);
	}

	if (GetAsyncKeyState('A') & 0x8001)
	{
		_vec3 vRot = m_pTransformCom->GetRotation();
		vRot.z -= 10.f * fTimeDelta;
		m_pTransformCom->SetRotation(vRot);
	}

	if (GetAsyncKeyState('D') & 0x8001)
	{
		_vec3 vRot = m_pTransformCom->GetRotation();
		vRot.z += 10.f * fTimeDelta;
		m_pTransformCom->SetRotation(vRot);
	}
}
