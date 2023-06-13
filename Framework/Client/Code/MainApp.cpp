#include "stdafx.h"
#include "..\Header\MainApp.h"


CMainApp::CMainApp()
{
}


CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp(void)
{
	return S_OK;
}

int CMainApp::Update_MainApp(const float & fTimeDelta)
{
	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
}

void CMainApp::Render_MainApp()
{
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
}
