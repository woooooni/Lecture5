#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CGameObject;
class ENGINE_DLL CComponent : public CBase
{
protected:
	explicit CComponent();
	explicit CComponent(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CComponent(const CComponent& rhs);
	virtual ~CComponent();

public:
	virtual	_int Update_Component(const _float& fTimeDelta) { return 0; }
	virtual void LateUpdate_Component(void) {}
	virtual void Render_Component(void) {};
public:
	CGameObject*	GetOwner()						{ return m_pOwner; }
	void			SetOwner(CGameObject* _pOwner)	{ m_pOwner = _pOwner; }

protected:
	LPDIRECT3DDEVICE9			m_pGraphicDev;
	_bool						m_bClone;
	CGameObject*				m_pOwner;
public:
	virtual CComponent*		Clone(void)		PURE;
	virtual void			Free(void)	override;
};

END