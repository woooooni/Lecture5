#pragma once

#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CGraphicDev;
class CManagement;

END
class CMainApp : public CBase 
{
private:		// 생성자, 소멸자
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT		Ready_MainApp(void);
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp();
	void		Render_MainApp();

private:
	HRESULT				SetUp_DefaultSetting(LPDIRECT3DDEVICE9* ppGraphicDev);
	HRESULT				Ready_Scene(LPDIRECT3DDEVICE9 pGraphicDev, Engine::CManagement** ppManagementClass);

private:
	CGraphicDev*			m_pDeviceClass;
	CManagement*			m_pManagementClass;

	LPDIRECT3DDEVICE9		m_pGraphicDev;

public:
	static CMainApp*		Create();

private:
	virtual void		Free();

};

// 1. 뷰스페이스 변환 함수와 원근 투영 행렬 제작 함수를 직접 만들어와라
// 2. 높이맵을 이용하여 지형의 높낮이를 적용해 와라