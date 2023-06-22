#include "Camera.h"
#include "Export_Function.h"

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pTransformCom(nullptr)
	, m_fFov(4.f)
{

}

CCamera::CCamera(const CCamera & rhs)
	: CGameObject(rhs)
	, m_fFov(4.f)
{

}

CCamera::~CCamera()
{
}

HRESULT CCamera::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransformCom->Set_Pos(&_vec3( 0.f, 10.f, -10.f ));
	return S_OK;
}

_int CCamera::Update_Object(const _float& fTimeDelta)
{
	_int iExit = __super::Update_Object(fTimeDelta);
	Key_Input(fTimeDelta);

	_vec3 vPos, vLook, vRight, vUp;
	ZeroMemory(&vPos, sizeof(_vec3));
	ZeroMemory(&vLook, sizeof(_vec3));
	ZeroMemory(&vUp, sizeof(_vec3));

	m_pTransformCom->Get_Info(MATRIX_INFO::INFO_POS, &vPos);
	m_pTransformCom->Get_Info(MATRIX_INFO::INFO_RIGHT, &vRight);
	m_pTransformCom->Get_Info(MATRIX_INFO::INFO_UP, &vUp);
	m_pTransformCom->Get_Info(MATRIX_INFO::INFO_LOOK, &vLook);
	

	m_matView = m_pTransformCom->Get_WorldInverseMatrix();
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / m_fFov, WINCX / WINCY, m_fNear, m_fFar);

	m_pGraphicDev->SetTransform(D3DTS_VIEW, &m_matView);
	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &m_matProj);

	return iExit;
}

void CCamera::LateUpdate_Object(void)
{
	__super::LateUpdate_Object();
}

void CCamera::Render_Object(void)
{

}

HRESULT CCamera::Add_Component(void)
{
	CComponent*			pComponent = nullptr;

	pComponent = m_pTransformCom = dynamic_cast<CTransform*>(Engine::Clone_Proto(L"Proto_Transform"));
	NULL_CHECK_RETURN(pComponent, E_FAIL);
	pComponent->SetOwner(this);
	m_mapComponent[ID_DYNAMIC].emplace(L"Com_Transform", pComponent);
	
	return S_OK;
}

void CCamera::Key_Input(const _float & fTimeDelta)
{
	_vec3 vLook, vDir, vRight, vPos;
	m_pTransformCom->Get_Info(INFO_LOOK, &vLook);
	m_pTransformCom->Get_Info(INFO_RIGHT, &vRight);
	m_pTransformCom->Get_Info(INFO_POS, &vPos);

	D3DXVec3Normalize(&vDir, &vLook);
	D3DXVec3Normalize(&vRight, &vRight);

	if (Engine::Get_DIKeyState(DIK_W) & 0x8000)
	{
		m_pTransformCom->Move_Pos(&vDir, fTimeDelta, 20.f);
	}

	if (Engine::Get_DIKeyState(DIK_S) & 0x8000)
	{
		m_pTransformCom->Move_Pos(&vDir, fTimeDelta, -20.f);
	}

	if (Engine::Get_DIKeyState(DIK_A) & 0x8000)
	{
		m_pTransformCom->Move_Pos(&vRight, fTimeDelta, -20.f);
	}

	if (Engine::Get_DIKeyState(DIK_D) & 0x8000)
	{
		m_pTransformCom->Move_Pos(&vRight, fTimeDelta, 20.f);
	}
	
	if (Engine::Get_DIMouseMove(MOUSEMOVESTATE::DIMS_X) > 0)
	{
		m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(60.f * fTimeDelta));
	}
	else if (Engine::Get_DIMouseMove(MOUSEMOVESTATE::DIMS_X) < 0)
	{
		m_pTransformCom->Rotation(ROT_Y, D3DXToRadian(60.f * -fTimeDelta));
	}

	if (Engine::Get_DIMouseMove(MOUSEMOVESTATE::DIMS_Y) > 0)
	{
		m_pTransformCom->Rotation(ROT_X, D3DXToRadian(60.f * fTimeDelta));
	}
	else if (Engine::Get_DIMouseMove(MOUSEMOVESTATE::DIMS_Y) < 0)
	{
		m_pTransformCom->Rotation(ROT_X, D3DXToRadian(60.f * -fTimeDelta));
	}

	if (Engine::Get_DIMouseMove(MOUSEMOVESTATE::DIMS_Z) > 0)
	{
		m_fFov += 10.f * fTimeDelta;

		if (m_fFov <= 1.f)
			m_fFov = 1.f;
	}

	else if (Engine::Get_DIMouseMove(MOUSEMOVESTATE::DIMS_Z) < 0)
	{
		m_fFov -= 10.f * fTimeDelta;

		if (m_fFov >= D3DX_PI)
			m_fFov = D3DX_PI;
	}

}

CCamera* CCamera::Create(LPDIRECT3DDEVICE9 pGraphicDev, _float fNear, _float fFar)
{
	CCamera*	pInstance = new CCamera(pGraphicDev);

	pInstance->Set_Near(fNear);
	pInstance->Set_Far(fFar);
	
	if (FAILED(pInstance->Ready_Object()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Camera Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CCamera::Free()
{
	CGameObject::Free();
}
