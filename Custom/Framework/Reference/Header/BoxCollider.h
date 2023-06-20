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


	_vec3					m_vCenter;			// ����.
	_vec3					m_vExtents;			// �������� �� ����� �Ÿ�.
	_vec3					m_vOrientation;		// ȸ���� ��Ÿ���� ����.



public:
	static CBoxCollider*	Create(LPDIRECT3DDEVICE9 _pDevice);
	virtual void			Free();
	virtual CComponent *	Clone(void) override;


};

END