#include "..\..\Header\Layer.h"

CLayer::CLayer()
{
	m_vecObject.reserve(100);
}

CLayer::~CLayer()
{
}

HRESULT CLayer::Add_GameObject(const wstring & _strObjName, CGameObject * pGameObject)
{
	pGameObject->Set_Name(_strObjName);
	m_vecObject.push_back(pGameObject);
	return S_OK;
}

CGameObject * CLayer::Find_GameObject(const wstring& _strObjName)
{
	for (_uint i = 0; i < m_vecObject.size(); ++i)
	{
		if (m_vecObject[i]->Get_Name() == _strObjName)
			return m_vecObject[i];
	}

	return nullptr;
}

HRESULT CLayer::Ready_Layer()
{
	return S_OK;
}

_int CLayer::Update_Layer(const _float & fTimeDelta)
{
	_int		iResult = 0;

	for (auto& iter : m_vecObject)
	{
		iResult = iter->Update_Object(fTimeDelta);

		if (iResult & 0x80000000)
			return iResult;
	}
	
	return iResult;
}

void CLayer::LateUpdate_Layer()
{
	for (auto& iter : m_vecObject)
		iter->LateUpdate_Object();
}

CLayer * CLayer::Create()
{
	CLayer *	pInstance = new CLayer;

	if (FAILED(pInstance->Ready_Layer()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Layer Create Failed");
		return nullptr;
	}

	return pInstance;
}

void CLayer::Free()
{
	for_each(m_vecObject.begin(), m_vecObject.end(), CDeleteObj());
	m_vecObject.clear();
	m_vecObject.shrink_to_fit();
}
