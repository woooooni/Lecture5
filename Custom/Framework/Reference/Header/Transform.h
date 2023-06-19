#pragma once
#include "Component.h"

BEGIN(Engine)

class ENGINE_DLL CTransform : public CComponent
{
private:
	explicit CTransform();
	explicit CTransform(LPDIRECT3DDEVICE9 pDevice);
	explicit CTransform(const CTransform& rhs);
	virtual ~CTransform();

public:
	virtual HRESULT			Ready_Transform();

public:
	virtual	_int Update_Component(const _float& fTimeDelta);
	virtual void LateUpdate_Component(void);

public:
	const _matrix&	GetWorldMat() const { return m_matWorld; }
	const _vec3&	GetPosition() const	{ return m_vPos; }
	const _vec3&	GetRotation() const { return m_vRot; }
	const _vec3&	GetScale()	const	{ return m_vScale; }
	const _vec3&	GetLookAt() const	{ return m_vLookAt; }

	void SetPosition(const _vec3& _vPos)		{ m_vPos = _vPos; }
	void SetRotation(const _vec3& _vRotation)	{ m_vRot = _vRotation; }
	void SetScale(const _vec3& _vScale)			{ m_vScale = _vScale; }
	void SetLookAt(const _vec3& _vLookAt)		{ m_vLookAt = _vLookAt; }

public:
	// CComponent을(를) 통해 상속됨
	virtual CComponent * Clone(void) override;
	virtual void Free() override;

public:
	static CTransform* Create(LPDIRECT3DDEVICE9 _pDevice);

private:
	_vec3		m_vPos;
	_vec3		m_vRot;
	_vec3		m_vScale;
	_vec3		m_vLookAt;

	_matrix		m_matWorld;
};

END