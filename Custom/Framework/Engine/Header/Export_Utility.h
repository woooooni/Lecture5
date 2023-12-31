#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Management.h"
#include "ProtoMgr.h"
#include "CameraMgr.h"
#include "Renderer.h"
#include "PickingMgr.h"
#include "LightMgr.h"

#include "TriCol.h"
#include "RcCol.h"
#include "RcTex.h"
#include "RcTerrain.h"
#include "RcCube.h"

#include "Transform.h"
#include "Collider.h"
#include "BoxCollider.h"
#include "Texture.h"
#include "Animator.h"

#include "GameObject.h"



BEGIN(Engine)

inline HRESULT			Create_Management(LPDIRECT3DDEVICE9 pGraphicDev, CManagement** ppInstance);

inline HRESULT			Set_Scene(CScene* pScene);
inline _int				Update_Scene(const _float& fTimeDelta);
inline void				LateUpdate_Scene();
inline void				Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

inline CScene*			GetCurrScene();
inline CLayer*			Get_Layer(const _tchar* pLayerTag);

// ProtoMgr
inline HRESULT			Ready_Proto(const _tchar* pProtoTag, CComponent* pComponent);
inline CComponent*		Clone_Proto(const _tchar* pProtoTag);

// CameraMgr
inline CCamera*			CreateCamera(HWND _hWnd, LPDIRECT3DDEVICE9 _pDevice, _float _fNear, _float _fFar);

// Renderer
inline void				Add_RenderGroup(RENDERID eType, CGameObject* pGameObject);
inline void				Render_GameObject(LPDIRECT3DDEVICE9& pGraphicDev);
inline void				Clear_RenderGroup();

// PickingMgr
inline HRESULT			Ready_PickingMgr(LPDIRECT3DDEVICE9 _pDevice, HWND _hWnd);
inline void				Update_PickingMgr();
inline BOOL				IsPicking(CGameObject* _pObj, _vec3* _vHit);

// LightMgr
inline 	HRESULT		Ready_Light(LPDIRECT3DDEVICE9 pGraphicDev,
	const D3DLIGHT9* pLightInfo,
	const _uint& iIndex);

inline void				Release_Utility();

#include "Export_Utility.inl"

END

#endif // Export_Utility_h__


