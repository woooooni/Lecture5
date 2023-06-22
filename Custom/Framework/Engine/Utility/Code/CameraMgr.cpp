#include "..\..\Header\CameraMgr.h"

USING(Engine)
IMPLEMENT_SINGLETON(CCameraMgr)

CCameraMgr::CCameraMgr()
{

}

CCameraMgr::~CCameraMgr()
{
	Free();
}


CCamera * CCameraMgr::CreateCamera(LPDIRECT3DDEVICE9 _pDevice, _float _fNear, _float _fFar)
{
	CCamera* pCamera = nullptr; 
	pCamera = CCamera::Create(_pDevice, _fNear, _fFar);
	
	NULL_CHECK_RETURN(pCamera, nullptr);

	return pCamera;
}

void CCameraMgr::Free()
{
	
}
