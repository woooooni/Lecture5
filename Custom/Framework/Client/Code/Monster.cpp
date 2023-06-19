#include "stdafx.h"
#include "Monster.h"
#include "TimerMgr.h"
#include "Export_Utility.h"
#include "Transform.h"

CMonster::CMonster(LPDIRECT3DDEVICE9 pGraphicDev)
	:CGameObject(pGraphicDev)
	, m_pBufferCom(nullptr)
	, m_pTransformCom(nullptr)
{
}

CMonster::CMonster(const CGameObject & rhs)
	: CGameObject(rhs)
{

}

CMonster::~CMonster()
{
}

HRESULT CMonster::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	return S_OK;
}

_int CMonster::Update_Object(const _float & fTimeDelta)
{
	TraceTarget();
	return __super::Update_Object(fTimeDelta);
}

void CMonster::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CMonster::Render_Object(void)
{
	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	const _matrix& matWorld = m_pTransformCom->GetWorldMat();
	m_pGraphicDev->SetTransform(D3DTS_WORLD, &m_pTransformCom->GetWorldMat());
	m_pBufferCom->Render_Buffer();

	m_pGraphicDev->SetRenderState(D3DRS_CULLMODE, D3DCULL_CCW);
	__super::Render_Object();
}

HRESULT CMonster::Add_Component(void)
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

CMonster * CMonster::Create(LPDIRECT3DDEVICE9 _pDev)
{
	CMonster*	pInstance = new CMonster(_pDev);

	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Monster Create Failed");
		return nullptr;
	}

	return pInstance;

}

void CMonster::Free()
{
	__super::Free();
}

void CMonster::TraceTarget()
{
	if (nullptr == m_pTarget)
		return;
	
	
	const CTransform* pTargetTrans = dynamic_cast<CTransform*>(m_pTarget->Get_Component(L"Com_Transform", COMPONENTID::ID_DYNAMIC));

	_vec3 vPos = m_pTransformCom->GetPosition();

	const _vec3& vTargetPos = pTargetTrans->GetPosition();

	_vec3 vDir = vPos - vTargetPos;

	float fDist = D3DXVec3Length(&vDir);
	if (fDist < 0.1f)
		return;
	

	D3DXVec3Normalize(&vDir, &vDir);

	vPos -= vDir * 50.f * 0.0016f;
	
	m_pTransformCom->SetPosition(vPos);
}

