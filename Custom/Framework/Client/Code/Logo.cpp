#include "stdafx.h"
#include "..\Header\Logo.h"

#include "Export_Function.h"

CLogo::CLogo(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{
}

CLogo::~CLogo()
{
}

HRESULT CLogo::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);

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
	CLayer* pLayer = m_mapLayer[L"Environment"];

	CCamera* pCamera = nullptr;
	 pCamera = dynamic_cast<CCamera*>(pLayer->Get_GameObject(L"MainCamera"));

	if (pCamera != nullptr)
	{
		m_pGraphicDev->SetTransform(D3DTS_VIEW, &pCamera->GetViewMatrix());
		m_pGraphicDev->SetTransform(D3DTS_PROJECTION, &pCamera->GetProjectionMatrix());
	}
	__super::Render_Scene();
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
	// 프로토타입 컴포넌트 추가.
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_TriCol", CTriCol::Create(m_pGraphicDev)), E_FAIL);
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcCol", CRcCol::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcTex", CRcTex::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Transform", CTransform::Create(m_pGraphicDev)), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Texture_Logo", CTexture::Create(m_pGraphicDev, TEXTUREID::TEX_NORMAL, L"../Bin/Resource/Texture/Logo/IU.jpg")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Texture_Terrain", CTexture::Create(m_pGraphicDev, TEXTUREID::TEX_NORMAL, L"../Bin/Resource/Texture/Logo/IU.jpg")), E_FAIL);
	FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_RcTerrain", CRcTerrain::Create(m_pGraphicDev, 129, 129, 1)), E_FAIL);
	//FAILED_CHECK_RETURN(Engine::Ready_Proto(L"Proto_Collider", CCollider::Create(m_pGraphicDev)), E_FAIL);

	return S_OK;
}

HRESULT CLogo::Ready_Layer_Environment(const _tchar* pLayerTag)
{
	Engine::CLayer*		pLayer = Engine::CLayer::Create();
	NULL_CHECK_RETURN(pLayer, E_FAIL);

	Engine::CGameObject*		pGameObject = nullptr;

	
	/*pGameObject = CBackGround::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"BackGround", pGameObject), E_FAIL);*/

	// Terrain
	pGameObject = CTerrain::Create(m_pGraphicDev);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Terrain", pGameObject), E_FAIL);

	// Camera
	pGameObject = Engine::CreateCamera(m_pGraphicDev, 1.f, 1000.f);
	NULL_CHECK_RETURN(pGameObject, E_FAIL);
	FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"MainCamera", pGameObject), E_FAIL);
		
	//// Player
	//pGameObject = CPlayer::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Player", pGameObject), E_FAIL);

	//// Monster
	//pGameObject = CMonster::Create(m_pGraphicDev);
	//NULL_CHECK_RETURN(pGameObject, E_FAIL);
	//FAILED_CHECK_RETURN(pLayer->Add_GameObject(L"Monster", pGameObject), E_FAIL);

	m_mapLayer.insert({ pLayerTag, pLayer });

	return S_OK;
}
