#pragma once
#include "Base.h"
#include "Engine_Define.h"

BEGIN(ENGINE)
#include "Engine_Struct.h"
END
class CObj :
	public CBase
{
protected:
	explicit CObj();
	virtual ~CObj();

public:
	virtual HRESULT Ready_Obj(void)							PURE;
	virtual void	Update_Obj(const _float& _fDeltaTime)	PURE;
	virtual void	Late_Update_Obj()						PURE;
	virtual void	Render_Obj()							PURE;


protected:
	LPDIRECT3DVERTEXBUFFER9		m_pVB;
	LPDIRECT3DINDEXBUFFER9		m_pIB;

protected:
	vector<VTXCOL*>		m_vecVertices;
	vector<DWORD>		m_vecIndices;
	_matrix				m_matWorld;

	_vec3				m_vPos;
	_vec3				m_vSize;
	_vec3				m_vRotation;


public:
	virtual CObj*	Clone()									PURE;
	virtual void	Free()									PURE;

};
