#include "stdafx.h"
#include "..\Header\MainApp.h"
#include "Engine_Define.h"
#include "Export_Function.h"
#include "GraphicDev.h"
#include "Triangle.h"
#include "Cube.h"
CMainApp::CMainApp() : m_pDeviceClass(nullptr), m_pTriangle(nullptr)
{
	
}

CMainApp::~CMainApp()
{
}

HRESULT CMainApp::Ready_MainApp(void)
{
	FAILED_CHECK_RETURN(Engine::Ready_GraphicDev(g_hWnd, MODE_WIN, 800, 600, &m_pDeviceClass), E_FAIL);
	m_pTriangle = CTriangle::Create();
	m_pCube = CCube::Create();

	RECT	rect;
	D3DVIEWPORT9 vp;
	GetClientRect(g_hWnd, &rect);

	vp.X = 0;
	vp.Y = 0;
	vp.Width = 800;
	vp.Height = 600;
	vp.MinZ = 0.f;
	vp.MaxZ = 1.f;

	m_vEye.x = 0.f;
	m_vEye.y = 0.f;
	m_vEye.z = -5.f;

	m_vAt.x = 0.f;
	m_vAt.y = 0.f;
	m_vAt.z = 0.f;

	m_vUp.x = 0.f;
	m_vUp.y = 1.f;
	m_vUp.z = 0.f;

	Engine::Get_Device()->SetViewport(&vp);
	Engine::Get_Device()->SetRenderState(D3DRS_LIGHTING, FALSE);

	return S_OK;
}

int CMainApp::Update_MainApp(const float & fTimeDelta)
{
	m_pTriangle->Update_Obj(fTimeDelta);
	m_pCube->Update_Obj(fTimeDelta);
	return 0;
}

void CMainApp::LateUpdate_MainApp()
{
	m_pTriangle->Late_Update_Obj();
	m_pCube->Late_Update_Obj();
}

void CMainApp::Render_MainApp()
{
	Engine::Render_Begin(D3DXCOLOR(0.f, 0.f, 1.f, 1.f));
	
	Engine::Get_Device()->SetRenderState(D3DRS_CULLMODE, D3DCULL_NONE);
	
	D3DXMatrixIdentity(&m_matView);
	D3DXMatrixIdentity(&m_matProj);

	D3DXMatrixLookAtLH(&m_matView, &m_vEye, &m_vAt, &m_vUp);
	Engine::Get_Device()->SetTransform(D3DTS_VIEW, &m_matView);

	D3DXMatrixPerspectiveFovLH(&m_matProj, D3DX_PI / 4.f, 800 / 600, 1.f, 1000.f);
	Engine::Get_Device()->SetTransform(D3DTS_PROJECTION, &m_matProj);
	
	//m_pTriangle->Render_Obj();
	m_pCube->Render_Obj();
	
	Engine::Render_End();
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
	Engine::Release_System();
	Safe_Release(m_pTriangle);
	Safe_Release(m_pCube);
}
