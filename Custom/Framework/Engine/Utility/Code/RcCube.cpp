#include "..\..\Header\RcCube.h"



CRcCube::CRcCube()
{
}

CRcCube::CRcCube(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
{
}

CRcCube::CRcCube(const CRcCube & rhs)
	: CVIBuffer(rhs)
{
}


CRcCube::~CRcCube()
{
}

HRESULT CRcCube::Ready_Buffer(void)
{
	return S_OK;
}

void CRcCube::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

CRcCube * CRcCube::Create(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CRcCube *	pInstance = new CRcCube(pGraphicDev);

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		MSG_BOX("CubeVIBuffer Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CRcCube::Clone(void)
{
	return new CRcCube(*this);
}

void CRcCube::Free(void)
{
	CVIBuffer::Free();
}
