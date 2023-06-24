#include "Export_Utility.h"

IMPLEMENT_SINGLETON(CManagement)

CManagement::CManagement() : m_pScene(nullptr)
{
}

CManagement::~CManagement()
{
	Free();
}

CComponent * CManagement::Get_Component(const _tchar * pLayerTag, const _tchar * pObjTag, const _tchar * pComponentTag, COMPONENTID eID)
{
	if (nullptr == m_pScene)
		return nullptr;

	return m_pScene->Get_Component(pLayerTag, pObjTag, pComponentTag, eID);
}

HRESULT CManagement::Set_Scene(CScene * pScene)
{
	Safe_Release(m_pScene);

	Clear_RenderGroup();
	
	m_pScene = pScene;

	return S_OK;
}

_int CManagement::Update_Scene(const _float & fTimeDelta)
{
	if (nullptr == m_pScene)
		return -1;

	return m_pScene->Update_Scene(fTimeDelta);
}

void CManagement::LateUpdate_Scene()
{
	if (nullptr == m_pScene)
		return;

	m_pScene->LateUpdate_Scene();
}

void CManagement::Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	Engine::Render_GameObject(pGraphicDev);

	if (m_pScene)
		m_pScene->Render_Scene();
}

void CManagement::Free()
{
	Safe_Release(m_pScene);
}
