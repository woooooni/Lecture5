#pragma once

#include "GameObject.h"

BEGIN(Engine)

class CTerrainTex;
class CTexture;
class CTransform;

END

class CTerrain : public Engine::CGameObject
{
private:
	explicit CTerrain(LPDIRECT3DDEVICE9 pGraphicDev);
	explicit CTerrain(const CTerrain& rhs);
	virtual ~CTerrain();

public:
	virtual HRESULT Ready_Object(void) override;
	virtual _int Update_Object(const _float& fTimeDelta) override;
	virtual void LateUpdate_Object(void) override;
	virtual void Render_Object(void) override;

private:
	HRESULT		Add_Component(void);
	void		Key_Input(const _float& fTimeDelta);

private:
	CTerrainTex*			m_pBufferCom = nullptr;
	CTexture*		m_pTextureCom = nullptr;
	CTransform*		m_pTransformCom = nullptr;

	_vec3			m_vDir;
	_float			m_fSpeed;

public:
	static CTerrain*		Create(LPDIRECT3DDEVICE9 pGraphicDev);

private:
	virtual void Free() override;

};

// 1��Ī ī�޶� ����, W, A, S,D �� ī�޶� �̵�, ���콺�� �ٶ󺸴� �������� ī�޶� �ٶ󺸴� ���⵵ ȸ��