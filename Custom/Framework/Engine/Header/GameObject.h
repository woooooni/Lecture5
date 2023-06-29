#pragma once

#include "Engine_Define.h"
#include "Base.h"

BEGIN(Engine)

class CComponent;
class ENGINE_DLL CGameObject : public CBase
{
protected:
	explicit CGameObject(LPDIRECT3DDEVICE9 pGraphicDev, OBJ_TYPE _eType);
	explicit CGameObject(const CGameObject& rhs);
	virtual ~CGameObject();

public:
	const wstring&		Get_Name()							{ return m_strName; }
	void				Set_Name(const wstring& _strName)	{ m_strName = _strName; }
	CComponent*			Get_Component(const _tchar* pComponentTag, COMPONENTID eID);

public:
	virtual HRESULT		Ready_Object(void);
	virtual _int		Update_Object(const _float& fTimeDelta);
	virtual void		LateUpdate_Object(void);
	virtual void		Render_Object(void);

public:
	CComponent*			Find_Component(const _tchar* pComponentTag, COMPONENTID eID);
	OBJ_TYPE			Get_ObjType() { return m_eType; }
	void				Set_ObjType(OBJ_TYPE _eType) { m_eType = _eType; }
protected:
	map<const _tchar*, CComponent*>		m_mapComponent[ID_END];
	LPDIRECT3DDEVICE9					m_pGraphicDev;


private:
	wstring		m_strName;
	OBJ_TYPE	m_eType;


public:
	virtual void		Free();
};


END