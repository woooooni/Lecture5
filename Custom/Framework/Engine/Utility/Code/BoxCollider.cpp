#include "..\..\Header\BoxCollider.h"

CBoxCollider::CBoxCollider()
{
}

CBoxCollider::CBoxCollider(LPDIRECT3DDEVICE9 _pDevice)
	: CCollider(_pDevice)
{
}

CBoxCollider::CBoxCollider(const CBoxCollider & rhs)
	: CCollider(rhs)
{

}


CBoxCollider::~CBoxCollider()
{
}


HRESULT CBoxCollider::Ready_BoxCollider()
{
	return S_OK;
}

_int CBoxCollider::Update_Component(const _float & fTimeDelta)
{
	// TODO :: Update Vertex
	return __super::Update_Component(fTimeDelta);
}

void CBoxCollider::LateUpdate_Component()
{
}

CBoxCollider * CBoxCollider::Create(LPDIRECT3DDEVICE9 _pDevice)
{
	CBoxCollider*		pInstance = new CBoxCollider(_pDevice);

	if (FAILED(pInstance->Ready_BoxCollider()))
	{
		Safe_Release(pInstance);
		MSG_BOX("BoxCollider Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CBoxCollider::Free()
{
	CComponent::Free();
}

CComponent * CBoxCollider::Clone(void)
{
	return new CBoxCollider(*this);
}
