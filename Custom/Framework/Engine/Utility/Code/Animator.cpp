#include "..\..\Header\Animator.h"



CAnimator::CAnimator()
{
}

CAnimator::CAnimator(LPDIRECT3DDEVICE9 _pDevice)
{
}

CAnimator::CAnimator(const CAnimator & rhs)
{
}


CAnimator::~CAnimator()
{
}

HRESULT CAnimator::Ready_Animator(const wstring & _strPath)
{
	return E_NOTIMPL;
}

_int CAnimator::Update_Component(const _float & fTimeDelta)
{
	return _int();
}

void CAnimator::LateUpdate_Component()
{
}

void CAnimator::Render_Component()
{
}

CAnimator * CAnimator::Create(LPDIRECT3DDEVICE9 _pDevice, const wstring & _strPath)
{
	return nullptr;
}

void CAnimator::Free()
{
}

CComponent * CAnimator::Clone(void)
{
	return nullptr;
}
