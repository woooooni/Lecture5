#ifndef Export_System_h__
#define Export_System_h__

#include "GraphicDev.h"
#include "TimerMgr.h"
#include "FrameMgr.h"

BEGIN(Engine)

// GraphicDev
inline HRESULT				Ready_GraphicDev(HWND hWnd, WINMODE eMode, const _uint& iSizeX, const _uint& iSizeY, CGraphicDev** ppGraphicDev);
inline void					Render_Begin(D3DXCOLOR Color);
inline void					Render_End();
inline LPDIRECT3DDEVICE9	Get_Device();
// TimerMgr
inline _float		Get_TimeDelta(const _tchar* pTimerTag);
inline void			Set_TimeDelta(const _tchar* pTimerTag);
inline	HRESULT		Ready_Timer(const _tchar* pTimerTag);

// FrameMgr
inline _bool	Ispermit_Call(const _tchar* pFrameTag, const _float& fTimeDelta);
inline HRESULT Ready_Frame(const _tchar* pFrameTag, const _float& fCallLimit);

inline void			Release_System();

#include "Export_System.inl"

END

#endif // Export_System_h__


