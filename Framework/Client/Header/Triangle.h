#pragma once
#include "Obj.h"
class CTriangle :
	public CObj
{
private:
	explicit CTriangle();
	virtual ~CTriangle();


public:
	// CObj��(��) ���� ��ӵ�
	virtual HRESULT Ready_Obj(void) override;
	virtual void Update_Obj(const _float & _fDeltaTime) override;
	virtual void Late_Update_Obj() override;
	virtual void Render_Obj() override;

public:
	virtual void Free() override;

public:
	static CTriangle* Create();


public:
	virtual CObj * Clone() override;

};

