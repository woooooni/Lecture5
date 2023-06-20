#include "..\..\Header\Component.h"

CComponent::CComponent()
	: m_pGraphicDev(nullptr), m_bClone(false)
{
}

CComponent::CComponent(LPDIRECT3DDEVICE9 pGraphicDev)
	: m_pGraphicDev(pGraphicDev), m_bClone(false)
{
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();
}

CComponent::CComponent(const CComponent & rhs)
	: m_pGraphicDev(rhs.m_pGraphicDev), m_bClone(true)
{
	if (m_pGraphicDev)
		m_pGraphicDev->AddRef();
}

CComponent::~CComponent()
{
}

void CComponent::Free(void)
{
	Safe_Release(m_pGraphicDev);
}
