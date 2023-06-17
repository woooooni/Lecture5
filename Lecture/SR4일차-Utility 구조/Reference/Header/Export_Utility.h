#ifndef Export_Utility_h__
#define Export_Utility_h__

#include "Management.h"

BEGIN(Engine)

inline CComponent*			Get_Component(const _tchar* pLayerTag,
							const _tchar* pObjTag,
							const _tchar* pComponentTag,
							COMPONENTID eID);

inline HRESULT		Create_Management(LPDIRECT3DDEVICE9 pGraphicDev, CManagement** ppInstance);

inline HRESULT		Set_Scene(CScene* pScene);
inline _int			Update_Scene(const _float& fTimeDelta);
inline void			LateUpdate_Scene();
inline void			Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev);

inline void			Release_Utility();

#include "Export_Utility.inl"

END

#endif // Export_Utility_h__


