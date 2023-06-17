#pragma once
#include "C:\Users\xodnj\Desktop\Lecture5\Framework\Client\Header\Obj.h"
class CCube :
	public CObj
{
private:
	explicit CCube();
	virtual ~CCube();

public:
	// CObj을(를) 통해 상속됨
	virtual HRESULT Ready_Obj(void) override;
	virtual void Update_Obj(const _float & _fDeltaTime) override;
	virtual void Late_Update_Obj() override;
	virtual void Render_Obj() override;


private:
	void Input();

public:
	virtual void Free() override;

public:
	static CCube* Create();


public:
	virtual CObj * Clone() override;
};

