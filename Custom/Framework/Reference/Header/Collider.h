#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CCollider :
	public CComponent
{
public:
	explicit CCollider();
	explicit CCollider(LPDIRECT3DDEVICE9 _pDevice);
	explicit CCollider(const CCollider& rhs);
	virtual ~CCollider();

public:
	bool			IsEnable()			{ return m_bEnable; }
	void			SetEnable(bool _b)	{ m_bEnable = _b; }

private:
	bool			m_bEnable;
	bool			m_bRender;
};

END
