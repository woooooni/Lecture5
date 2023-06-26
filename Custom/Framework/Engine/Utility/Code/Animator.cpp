#include "..\..\Header\Animator.h"
#include "Texture.h"


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
	if (m_pCurAnimation == nullptr)
		return;

}

HRESULT CAnimator::Play_Animation(const wstring & _strKey)
{
	auto iter = m_mapTexture.find(_strKey);
	if (iter == m_mapTexture.end())
		NULL_CHECK_RETURN_MSG(nullptr, E_FAIL, L"Play_Animation Failed.");

	m_bFinished = false;
	m_pCurAnimation = iter->second;
}


CAnimator * CAnimator::Create(LPDIRECT3DDEVICE9 _pDevice, const wstring& _strKey, const wstring & _strPath)
{
	CAnimator*			pInstance = new CAnimator(_pDevice);

	if (FAILED(pInstance->Ready_Animator(_strPath)))
	{
		MSG_BOX("Animator Create Failed");
		Safe_Release(pInstance);
		return nullptr;
	}

	return pInstance;
}

void CAnimator::Free()
{
	for_each(m_mapTexture.begin(), m_mapTexture.end(), CDeleteMap());
	m_mapTexture.clear();
}

CComponent * CAnimator::Clone(void)
{
	return new CAnimator(*this);
}
