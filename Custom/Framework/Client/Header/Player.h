#pragma once

#include "GameObject.h"

BEGIN(Engine)
class CTriCol;
class CTransform;
END

class CPlayer :
	public CGameObject
{
private:
	explicit CPlayer(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CPlayer(const CGameObject& rhs);
	virtual ~CPlayer();

public:
	virtual HRESULT		Ready_Object(void);
	virtual _int		Update_Object(const _float& fTimeDelta);
	virtual void		LateUpdate_Object(void);
	virtual void		Render_Object(void);

public:
	HRESULT Add_Component(void);
	
public:
	static CPlayer*		Create(LPDIRECT3DDEVICE9 _pDev);

public:
	virtual void		Free();

private:
	void				Input();

private:
	CTriCol*			m_pBufferCom = nullptr;
	CTransform*			m_pTransformCom = nullptr;
};

