#pragma once
#include "GameObject.h"

BEGIN(Engine)

class CRcTex;
class CTransform;
class CCollider;
class CTexture;
class CAnimator;

END
class CUI : public CGameObject
{
private:
	explicit CUI(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CUI(const CUI& rhs);
	virtual ~CUI();

public:
	virtual HRESULT		Ready_Object(void) override;
	virtual _int		Update_Object(const _float& fTimeDelta) override;
	virtual void		LateUpdate_Object(void) override;
	virtual void		Render_Object(void) override;



protected:
	CRcTex* m_pBufferCom = nullptr;
	CTransform* m_pTransformCom = nullptr;
	CCollider* m_pColliderCom = nullptr;
	CAnimator* m_pAnimator = nullptr;

protected:
	_matrix m_matProj;
	_matrix m_matView;


public:
	static CUI* Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;
};

