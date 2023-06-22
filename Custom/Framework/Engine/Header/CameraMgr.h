#pragma once

#include "Base.h"
#include "Camera.h"

BEGIN(Engine)

class ENGINE_DLL CCameraMgr : public CBase
{
	DECLARE_SINGLETON(CCameraMgr)

private:
	explicit CCameraMgr();
	virtual ~CCameraMgr();

public:
	CCamera* CreateCamera(LPDIRECT3DDEVICE9 _pDevice, _float _fNear, _float _fFar);


public:
	virtual void Free() override;
};

END