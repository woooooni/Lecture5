#include "..\..\Header\Layer.h"

CLayer::CLayer()
{
}

CLayer::~CLayer()
{
}

CComponent * CLayer::Get_Component(const _tchar * pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	auto iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_mapObject.end())
		return nullptr;
	
	return iter->second->Get_Component(pComponentTag, eID);
}


HRESULT CLayer::Add_GameObject(const _tchar * pObjTag, CGameObject * pGameObject)
{
	if (nullptr == pGameObject)
		return E_FAIL;

	m_mapObject.insert({ pObjTag, pGameObject });

	return S_OK;
}


CGameObject * CLayer::Get_GameObject(const _tchar * pObjTag)
{
	auto iter = find_if(m_mapObject.begin(), m_mapObject.end(), CTag_Finder(pObjTag));

	if (iter == m_mapObject.end())
		return nullptr;

	return iter->second;
}

HRESULT CLayer::Ready_Layer()
{
	return S_OK;
}

_int CLayer::Update_Layer(const _float & fTimeDelta)
{
	_int		iResult = 0;

	for (auto& iter : m_mapObject)
	{
		iResult = iter.second->Update_Object(fTimeDelta);

		if (iResult & 0x80000000)
			return iResult;
	}
	
	return iResult;
}

void CLayer::LateUpdate_Layer()
{
	for (auto& iter : m_mapObject)
		iter.second->LateUpdate_Object();
}

void CLayer::Render_Layer()
{
	for (auto& iter : m_mapObject)
		iter.second->Render_Object();
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
	for_each(m_mapObject.begin(), m_mapObject.end(), CDeleteMap());
	m_mapObject.clear();
}
