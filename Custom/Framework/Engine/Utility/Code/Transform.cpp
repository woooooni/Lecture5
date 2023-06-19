#include "..\..\Header\Transform.h"


CTransform::CTransform()
{
}

CTransform::CTransform(LPDIRECT3DDEVICE9 pDevice)
	:CComponent(pDevice)
{
}

CTransform::CTransform(const CTransform & rhs)
	: CComponent(rhs)
	, m_vPos(rhs.m_vPos)
	, m_vRot(rhs.m_vRot)
	, m_vScale(rhs.m_vScale)
	, m_vLookAt(rhs.m_vLookAt)
	, m_matWorld(rhs.m_matWorld)
{
}


CTransform::~CTransform()
{
}

HRESULT CTransform::Ready_Transform()
{
	m_vPos = _vec3{0.f, 0.f, 0.f };
	m_vRot = _vec3{0.f, 0.f, 0.f };
	m_vScale = _vec3{1.f, 1.f, 1.f };
	m_vLookAt = _vec3{ 0.f, 1.f, 0.f };

	D3DXMatrixIdentity(&m_matWorld);
	
	return S_OK;
}


_int CTransform::Update_Component(const _float & fTimeDelta)
{
	_matrix matTrans, matRot, matScale;
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);
	D3DXMatrixRotationYawPitchRoll(&matRot, m_vRot.y, m_vRot.x, m_vRot.z);
	D3DXMatrixScaling(&matScale, m_vScale.x, m_vScale.y, m_vScale.z);

	D3DXMatrixIdentity(&m_matWorld);
	m_matWorld = matScale * matRot * matTrans;

	return __super::Update_Component(fTimeDelta);
}

void CTransform::LateUpdate_Component(void)
{
	__super::LateUpdate_Component();
}

CComponent * CTransform::Clone(void)
{
	return new CTransform(*this);
}

void CTransform::Free()
{
	CComponent::Free();
}

CTransform * CTransform::Create(LPDIRECT3DDEVICE9 _pDevice)
{
	CTransform* pInstance = new CTransform(_pDevice);
	if (FAILED(pInstance->Ready_Transform()))
	{
		Safe_Release(pInstance);
		MSG_BOX("Transform Create Failed");
		return nullptr;
	}
	return pInstance;
}


