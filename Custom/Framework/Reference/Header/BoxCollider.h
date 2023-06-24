#pragma once
#include "Collider.h"

BEGIN(Engine)
class CRcCube;
class ENGINE_DLL CBoxCollider : public CCollider
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
	virtual void	Render_Component()	override;

public:
	// CCollider��(��) ���� ��ӵ�
	virtual void	OnCollisionEnter(CCollider * _pOther) override;
	virtual void	OnCollisionStay(CCollider * _pOther) override;
	virtual void	OnCollisionExit(CCollider * _pOther) override;

public:
	static CBoxCollider*	Create(LPDIRECT3DDEVICE9 _pDevice);
	virtual void			Free();
	virtual CComponent *	Clone(void) override;

private:
	CRcCube*	m_pBuffer;



};

END