#pragma once

#include "Base.h"
#include "Engine_Define.h"

BEGIN(Engine)

class CGraphicDev;

END

class CTriangle;
class CCube;
class CMainApp : public CBase 
{
private:		// 持失切, 社瑚切
	explicit CMainApp();
	virtual ~CMainApp();

public:
	HRESULT		Ready_MainApp(void);
	int			Update_MainApp(const float& fTimeDelta);
	void		LateUpdate_MainApp();
	void		Render_MainApp();

public:
	const _matrix&	GetViewMatrix() { return m_matView; }
	const _matrix&	GetProjMatrix() { return m_matProj; }

	const _vec3&	GetEye() { return m_vEye; }
	const _vec3&	GetAt() { return m_vEye; }
	const _vec3&	GetUp() { return m_vEye; }

private:
	CGraphicDev*	m_pDeviceClass;
	CTriangle*		m_pTriangle;
	CCube*			m_pCube;

	_vec3			m_vEye;
	_vec3			m_vAt;
	_vec3			m_vUp;

	_matrix			m_matView;
	_matrix			m_matProj;

public:
	static CMainApp*		Create();

private:
	virtual void		Free();

};

