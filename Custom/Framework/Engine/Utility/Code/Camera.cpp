#include "Camera.h"
#include "Export_Function.h"

CCamera::CCamera(LPDIRECT3DDEVICE9 pGraphicDev)
	: CGameObject(pGraphicDev)
	, m_pTransformCom(nullptr)
{

}

CCamera::CCamera(const CCamera & rhs)
	: CGameObject(rhs)
{

}

CCamera::~CCamera()
{
}

HRESULT CCamera::Ready_Object(void)
{
	FAILED_CHECK_RETURN(Add_Component(), E_FAIL);
	m_pTransformCom->Set_Pos(&_vec3( 0.f, 10.f, 0.f ));
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
	

	D3DXMatrixLookAtLH(&m_matView, &vPos, &vLook, &vUp);
	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.f, WINCX / WINCY, m_fNear, m_fFar);

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
	_ulong diffX = Engine::Get_DIMouseMove(MOUSEMOVESTATE::DIMS_X);
	_ulong diffY = Engine::Get_DIMouseMove(MOUSEMOVESTATE::DIMS_Y);
	_ulong diffZ = Engine::Get_DIMouseMove(MOUSEMOVESTATE::DIMS_Z);

	if (Engine::Get_DIKeyState(DIK_W))
	{
		_vec3 vPos, vLook;
		m_pTransformCom->Get_Info(INFO_LOOK, &vLook);
		D3DXVec3Normalize(&vLook, &vLook);

		m_pTransformCom->Get_Info(INFO_POS, &vPos);

		vPos += vLook * 5.f * fTimeDelta;

		m_pTransformCom->Set_Pos(&vPos);
	}

	if (Engine::Get_DIKeyState(DIK_S))
	{
		_vec3 vPos, vLook;
		m_pTransformCom->Get_Info(INFO_LOOK, &vLook);
		D3DXVec3Normalize(&vLook, &vLook);

		m_pTransformCom->Get_Info(INFO_POS, &vPos);

		vPos -= vLook * 5.f * fTimeDelta;

		m_pTransformCom->Set_Pos(&vPos);
	}

	//if (diffX > 0)
	//{
	//	//오른쪽 무브
	//	_vec3 vRot = m_pTransformCom->GetRotation();
	//	vRot.y += 5.f * fTimeDelta;
	//	m_pTransformCom->SetRotation(vRot);
	//}

	//else if (diffX < 0)
	//{
	//	_vec3 vRot = m_pTransformCom->GetRotation();
	//	vRot.y -= 5.f * diffX * fTimeDelta;
	//	m_pTransformCom->SetRotation(vRot);
	//}
	
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
