#pragma once
#include "GameObject.h"
#include "Transform.h"

BEGIN(Engine)

class ENGINE_DLL CCamera : public CGameObject
{
protected:
	explicit CCamera(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CCamera(const CCamera& rhs);
	virtual ~CCamera();

public:
	virtual HRESULT		Ready_Object(void);
	virtual _int		Update_Object(const _float& fTimeDelta);
	virtual void		LateUpdate_Object(void);
	virtual void		Render_Object(void);

public:
	const _matrix&	GetViewMatrix() { return m_matView; }
	const _matrix&	GetProjectionMatrix() { return m_matProj; }

	void		Set_Near(_float _f) { m_fNear = _f; }
	void		Set_Far(float _f)	{ m_fFar = _f; }

private:
	HRESULT		Add_Component(void);
	void		Key_Input(const _float& fTimeDelta);

private:
	CTransform*	m_pTransformCom = nullptr;
	_matrix		m_matView;
	_matrix		m_matProj;
	
	_float		m_fNear;
	_float		m_fFar;


public:
	static CCamera*		Create(LPDIRECT3DDEVICE9 pGraphicDev, _float fNear, _float fFar);
	virtual void		Free()	override;
};

END