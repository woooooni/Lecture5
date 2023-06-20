#pragma once
#include "Collider.h"

BEGIN(Engine)

class ENGINE_DLL CBoxCollider :
	public CCollider
{
public:
	explicit CBoxCollider();
	explicit CBoxCollider(LPDIRECT3DDEVICE9 _pDevice);
	explicit CBoxCollider(const CBoxCollider& rhs);
	virtual ~CBoxCollider();

public:
	HRESULT			Ready_BoxCollider();
	virtual	_int	Update_Component(const _float& fTimeDelta) override;
	virtual void	LateUpdate_Component() override;


private:
	LPDIRECT3DVERTEXBUFFER9	m_pVB = nullptr;
	LPDIRECT3DINDEXBUFFER9	m_pIB = nullptr;


	_vec3					m_vCenter;			// 중점.
	_vec3					m_vExtents;			// 중점에서 각 면까지 거리.
	_vec3					m_vOrientation;		// 회전을 나타내는 단위.



public:
	static CBoxCollider*	Create(LPDIRECT3DDEVICE9 _pDevice);
	virtual void			Free();
	virtual CComponent *	Clone(void) override;


};

END