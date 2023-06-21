#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CTriCol;
class CTransform;
class CCollider;

END

class CTerrain : public CGameObject
{
private:
	explicit CTerrain(LPDIRECT3DDEVICE9 _pDevice);
	explicit CTerrain(const CTerrain& rhs);
	virtual ~CTerrain();

private:
	HRESULT		Add_Component(void);

private:
	CTriCol*			m_pBufferCom = nullptr;
	CTransform*			m_pTransformCom = nullptr;
	CCollider*			m_pColliderCom = nullptr;
	_float				m_fSpeed = 5.f;

public:
	static CTerrain*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

