#include "stdafx.h"
#include "..\Header\MainApp.h"

#include "Engine_Define.h"
#include "Export_Function.h"
#include "Logo.h"

CMainApp::CMainApp() : m_pDeviceClass(nullptr), m_pManagementClass(nullptr)
{
	
}

CMainApp::~CMainApp()
{
	Free();
}

HRESULT CMainApp::Ready_MainApp(void)
{
	FAILED_CHECK_RETURN(SetUp_DefaultSetting(&m_pGraphicDev), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Scene(m_pGraphicDev, &m_pManagementClass), E_FAIL);
		

	return S_OK;
}

int CMainApp::Update_MainApp(const float & fTimeDelta)
{
	NULL_CHECK_RETURN(m_pManagementClass, -1);
	m_pManagementClass->Update_Scene(fTimeDelta);

	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
	NULL_CHECK(m_pManagementClass);
	m_pManagementClass->LateUpdate_Scene();
}

void CMainApp::Render_MainApp()
{
	m_pGraphicDev->SetRenderState(D3DRS_LIGHTING, FALSE);

	Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));

	m_pManagementClass->Render_Scene(m_pGraphicDev);

	Engine::Render_End();

}

HRESULT CMainApp::SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev)
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, 800, 600, &m_pDeviceClass), E_FAIL);
	m_pDeviceClass->AddRef();

	(*ppGraphicDev) = m_pDeviceClass->Get_GraphicDev();
	(*ppGraphicDev)->AddRef();
	
	return S_OK;
}

HRESULT CMainApp::Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement ** ppManagementClass)
{
	Engine::CScene*		pScene = nullptr;

	pScene = CLogo::Create(pGraphicDev);
	NULL_CHECK_RETURN(pScene, E_FAIL);

	FAILED_CHECK_RETURN(Engine::Create_Management(pGraphicDev, ppManagementClass), E_FAIL);
	(*ppManagementClass)->AddRef();

	FAILED_CHECK_RETURN((*ppManagementClass)->Set_Scene(pScene), E_FAIL);

	return S_OK;
}

CMainApp * CMainApp::Create()
{
	CMainApp *	pInstance = new	CMainApp;

	if (FAILED(pInstance->Ready_MainApp()))
	{
		delete pInstance;
		pInstance = nullptr;

		return pInstance;
	}
	
	return pInstance;
}

void CMainApp::Free()
{
	Safe_Release(m_pGraphicDev);

	Safe_Release(m_pDeviceClass);
	Safe_Release(m_pManagementClass);
		
	Engine::Release_Utility();
	Engine::Release_System();
}
