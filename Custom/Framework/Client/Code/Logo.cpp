#include "..\Header\Logo.h"

#include "Export_Function.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev, SCENE_TYPE::LOADING)
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(LAYER_TYPE::ENVIRONMENT), E_FAIL);

	D3DVIEWPORT9 vp;
	vp.X = 0;
	vp.Y = 0;
	vp.Width = WINCX;
	vp.Height = WINCY;
	vp.MinZ = 0.0f;
	vp.MaxZ = 1.0f;

	m_pGraphicDev->SetViewport(&vp);

	return S_OK;
}

Engine::_int CLogo::Update_Scene(const _float& fTimeDelta)
{

	__super::Update_Scene(fTimeDelta);

	return 0;
}

void CLogo::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();
}

void CLogo::Render_Scene()
{
	//CLayer* pLayer = m_mapLayer[L"Environment"];

	//CCamera* pCamera = nullptr;
	// pCamera = dynamic_cast<CCamera*>(pLayer->Get_GameObject(L"MainCamera"));

	//if (pCamera != nullptr)
	//{
	//	m_pGraphicDev->SetTransform(D3DTS_VIEW, &pCamera->GetViewMatrix());
	//	m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &pCamera->GetProjectionMatrix());
	//}
}

void CLogo::Free()
{
	__super::Free();
}

CLogo* CLogo::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CLogo*	pInstance = new CLogo(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Logo Create Failed");
		return nullptr;
	}

	return pInstance;
}

HRESULT CLogo::Ready_Prototype()
{
	return S_OK;
}

HRESULT CLogo::Ready_Layer_Environment(LAYER_TYPE _eType)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	//Terrain
	CTerrain* pTerrain = CTerrain::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pTerrain, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain", pTerrain), E_FAIL);

	// Player
	CPlayer* pPlayer = CPlayer::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pPlayer, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Player", pPlayer), E_FAIL);

	// Camera
	CCamera* pCamera = Engine::CreateCamera(g_hWnd, m_pGraphicDev, 1.f, 1000.f);
	NULL_CHECK_RETURN(pCamera, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MainCamera", pCamera), E_FAIL);
	
	pCamera->Set_TargetObj(pPlayer);

	

	m_mapLayer.insert({ _eType, pLayer });

	return S_OK;
}
