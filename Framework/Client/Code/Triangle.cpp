#include "stdafx.h"
#include "..\Header\Triangle.h"
#include "Export_System.h"
#include "GraphicDev.h"

CTriangle::CTriangle()
{
}


CTriangle::~CTriangle()
{
}

HRESULT CTriangle::Ready_Obj(void)
{
	LPDIRECT3DDEVICE9 pDevice = Engine::Get_Device();

	VTXCOL vertices[] =
	{
		{ D3DXVECTOR3{ -1.f,	-1.f,	1.f }, D3DCOLOR_RGBA(0, 255, 0, 255) },
		{ D3DXVECTOR3{ 0.f,		1.f,	1.f }, D3DCOLOR_RGBA(255, 0, 0, 255) },
		{ D3DXVECTOR3{ 1.f,		-1.f,	1.f }, D3DCOLOR_RGBA(0, 0, 255, 255) }
	};

	for (UINT i = 0; i < sizeof(vertices) / sizeof(VTXCOL); ++i)
		m_vecVertices.push_back(vertices[i]);

	pDevice->CreateVertexBuffer(sizeof(vertices), 0, D3DFVF_XYZ | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &m_pVB, NULL);

	void* pVertices;
	m_pVB->Lock(0, sizeof(vertices), &pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();

	pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VTXCOL));
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);
	return S_OK;
}

void CTriangle::Update_Obj(const _float & _fDeltaTime)
{

}

void CTriangle::Late_Update_Obj()
{

}

void CTriangle::Render_Obj()
{
	D3DXMatrixIdentity(&m_matWolrd);

	for (UINT i = 0; i < m_vecVertices.size(); ++i)
		D3DXVec3TransformCoord(&m_vecVertices[i].vPosition, &m_vecVertices[i].vPosition, &m_matWolrd);

	LPDIRECT3DDEVICE9 pDevice = Engine::Get_Device();
	pDevice->SetTransform(D3DTS_WORLD, &m_matWolrd);
	pDevice->DrawPrimitive(D3DPT_TRIANGLELIST, 0, 1);
}

void CTriangle::Free()
{
	
}

CTriangle * CTriangle::Create()
{
	CTriangle*	pInstance = new	CTriangle;

	if (FAILED(pInstance->Ready_Obj()))
	{
		delete pInstance;
		pInstance = nullptr;

		return pInstance;
	}

	return pInstance;
}

CObj * CTriangle::Clone()
{
	return new CTriangle(*this);
}
