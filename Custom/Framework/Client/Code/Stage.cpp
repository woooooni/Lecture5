#include "stdafx.h"
#include "..\Header\Stage.h"

#include "Export_Function.h"

CStage::CStage(LPDIRECT3DDEVICE9 pGraphicDev)
	: Engine::CScene(pGraphicDev)
{
}

CStage::~CStage()
{
}

HRESULT CStage::Ready_Scene()
{
	FAILED_CHECK_RETURN(Ready_Prototype(), E_FAIL);

	FAILED_CHECK_RETURN(Ready_Layer_Environment(L"Environment"), E_FAIL);
	


	return S_OK;
}

Engine::_int CStage::Update_Scene(const _float& fTimeDelta)
{

	__super::Update_Scene(fTimeDelta);

	return 0;
}

void CStage::LateUpdate_Scene()
{
	__super::LateUpdate_Scene();
}

void CStage::Render_Scene()
{
	
}

void CStage::Free()
{
	__super::Free();
}

CStage* CStage::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CStage*	pInstance = new CStage(pGraphicDev);

	if (FAILED(pInstance->Ready_Scene()))
	{
		Safe_Release(pInstance);

		MSG_BOX("Logo Create Failed");
		return nullptr;
	}

	return pInstance;
}

HRESULT CStage::Ready_Prototype()
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

HRESULT CStage::Ready_Layer_Environment(const _tchar* pLayerTag)
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
