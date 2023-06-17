#include "stdafx.h"
#include "Cube.h"
#include "Export_System.h"

CCube::CCube()
{
}


CCube::~CCube()
{
}

HRESULT CCube::Ready_Obj(void)
{
	LPDIRECT3DDEVICE9 pDevice = Engine::Get_Device();

	VTXCOL vertices[] =
	{
		{ D3DXVECTOR3{ -.5f,	.5f,	.5f }, D3DCOLOR_RGBA(255, 255, 0, 255) },
		{ D3DXVECTOR3{ .5f,		.5f,	.5f }, D3DCOLOR_RGBA(0, 255, 255, 255) },
		{ D3DXVECTOR3{ .5f,		.5f,	-.5f }, D3DCOLOR_RGBA(255, 255, 0, 255) },
		{ D3DXVECTOR3{ -.5f,	.5f,	-.5f }, D3DCOLOR_RGBA(255, 0, 255, 255) },

		{ D3DXVECTOR3{ -.5f,	-.5f,	.5f }, D3DCOLOR_RGBA(255, 0, 255, 255) },
		{ D3DXVECTOR3{ .5f,	-.5f,	.5f }, D3DCOLOR_RGBA(0, 255, 255, 255) },
		{ D3DXVECTOR3{ .5f,	-.5f,	-.5f }, D3DCOLOR_RGBA(255, 255, 0, 255) },
		{ D3DXVECTOR3{ -.5f,	-.5f,	-.5f }, D3DCOLOR_RGBA(0, 255, 0, 255) },
	};

	WORD Indices[] =
	{
		0, 1, 2,
		0, 2, 3,
		4, 6, 5,
		4, 7, 6,
		0, 3, 7,
		0, 7, 4,
		1, 5, 6,
		1, 6, 2,
		3, 2, 6,
		3, 6, 7,
		0, 4, 5,
		0, 5, 1
	};



	for (UINT i = 0; i < sizeof(vertices) / sizeof(VTXCOL); ++i)
		m_vecVertices.push_back(&vertices[i]);

	for (UINT i = 0; i < sizeof(Indices) / sizeof(WORD); ++i)
		m_vecIndices.push_back(Indices[i]);

	pDevice->CreateVertexBuffer(sizeof(vertices), 0, D3DFVF_XYZ | D3DFVF_DIFFUSE, D3DPOOL_DEFAULT, &m_pVB, NULL);
	pDevice->CreateIndexBuffer(sizeof(Indices), 0, D3DFMT_INDEX16, D3DPOOL_DEFAULT, &m_pIB, NULL);


	void* pVertices;
	m_pVB->Lock(0, sizeof(vertices), &pVertices, 0);
	memcpy(pVertices, vertices, sizeof(vertices));
	m_pVB->Unlock();

	// 4. ÀÎµ¦½º Á¤º¸¸¦ ÀÎµ¦½º ¹öÆÛ¿¡ º¹»ç.
	void*	pIndices;
	m_pIB->Lock(0, sizeof(Indices), &pIndices, 0);
	memcpy(pIndices, Indices, sizeof(Indices));
	m_pIB->Unlock();

	m_vPos = { 0.f, 0.f, 0.f };

	
	return S_OK;
}

void CCube::Update_Obj(const _float & _fDeltaTime)
{
	Input();
}

void CCube::Late_Update_Obj()
{

}

void CCube::Render_Obj()
{
	LPDIRECT3DDEVICE9 pDevice = Engine::Get_Device();

	pDevice->SetStreamSource(0, m_pVB, 0, sizeof(VTXCOL));
	pDevice->SetIndices(m_pIB);
	pDevice->SetFVF(D3DFVF_XYZ | D3DFVF_DIFFUSE);

	D3DXMATRIX matScale, matRot, matTrans;
	D3DXMatrixIdentity(&m_matWorld);

	D3DXMatrixScaling(&matScale, 1, 1, 1);
	D3DXMatrixRotationYawPitchRoll(&matRot, m_vRotation.y, m_vRotation.x, m_vRotation.z);
	D3DXMatrixTranslation(&matTrans, m_vPos.x, m_vPos.y, m_vPos.z);

	m_matWorld = matScale * matRot * matTrans;
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_WIREFRAME);
	pDevice->SetTransform(D3DTS_WORLD, &m_matWorld);
	pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 8, 0, 12);
	pDevice->SetRenderState(D3DRS_FILLMODE, D3DFILL_SOLID);

}

void CCube::Input()
{
	if (GetAsyncKeyState(VK_LEFT) & 0x8001)
	{
		m_vPos.x -= 100.f * 0.0016f;
	}

	if (GetAsyncKeyState(VK_RIGHT) & 0x8001)
	{
		m_vPos.x += 100.f * 0.0016f;
	}

	if (GetAsyncKeyState(VK_UP) & 0x8001)
	{
		m_vPos.y += 100.f * 0.0016f;
	}

	if (GetAsyncKeyState(VK_DOWN) & 0x8001)
	{
		m_vPos.y -= 100.f * 0.0016f;
	}

	if (GetAsyncKeyState('W') & 0x8001)
	{
		m_vRotation.x += 100.f * 0.0016f;
	}

	if (GetAsyncKeyState('A') & 0x8001)
	{
		m_vRotation.y += 100.f * 0.0016f;
	}

	if (GetAsyncKeyState('S') & 0x8001)
	{
		m_vRotation.x -= 100.f * 0.0016f;
	}

	if (GetAsyncKeyState('D') & 0x8001)
	{
		m_vRotation.y -= 100.f * 0.0016f;
	}

	if (GetAsyncKeyState('Q') & 0x8001)
	{
		m_vRotation.z += 100.f * 0.0016f;
	}

	if (GetAsyncKeyState('E') & 0x8001)
	{
		m_vRotation.z -= 100.f * 0.0016f;
	}

	if (GetAsyncKeyState('R') & 0x8000)
	{
		m_vRotation = { 0.f, 0.f, 0.f };
		m_vPos = { 0.f, 0.f, 0.f };
	}

	if (GetAsyncKeyState('T') & 0x8000)
	{
		// Áü¹ú¶ô À¯µµ.
		m_vRotation = { -90.f, 0.f, 0.f };
		m_vPos = { 0.f, 0.f, 0.f };
	}
}

void CCube::Free()
{

}

CCube * CCube::Create()
{
	CCube*	pInstance = new	CCube;

	if (FAILED(pInstance->Ready_Obj()))
	{
		delete pInstance;
		pInstance = nullptr;

		return pInstance;
	}

	return pInstance;
}

CObj * CCube::Clone()
{
	return new CCube(*this);
}
