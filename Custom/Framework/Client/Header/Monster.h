#pragma once

#include "GameObject.h"

BEGIN(Engine)
class CTriCol;
class CTransform;
END

class CMonster :
	public CGameObject
{
private:
	explicit CMonster(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CMonster(const CGameObject& rhs);
	virtual ~CMonster();

public:
	virtual HRESULT		Ready_Object(void);
	virtual _int		Update_Object(const _float& fTimeDelta);
	virtual void		LateUpdate_Object(void);
	virtual void		Render_Object(void);

public:
	HRESULT Add_Component(void);

public:
	static CMonster*		Create(LPDIRECT3DDEVICE9 _pDev);

public:
	virtual void		Free();

public:
	void				SetTarget(CGameObject* _pTarget) { m_pTarget = _pTarget; }

private:
	void				TraceTarget();

private:
	CTriCol*			m_pBufferCom = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CGameObject*		m_pTarget = nullptr;

};

