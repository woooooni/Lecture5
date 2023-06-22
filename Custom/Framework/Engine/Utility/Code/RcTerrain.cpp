#include "..\..\Header\RcTerrain.h"



CRcTerrain::CRcTerrain()
{
}

CRcTerrain::CRcTerrain(LPDIRECT3DDEVICE9 pGraphicDev)
	: CVIBuffer(pGraphicDev)
	, m_iVertexCountRow(0)
	, m_iVertexCountCol(0)
	, m_iCellSpacing(1)
	, m_iCellCountRow(0)
	, m_iCellCountCol(0)
	, m_iWidth(0)
	, m_iHeight(0)
{
}

CRcTerrain::CRcTerrain(const CRcTerrain & rhs)
	: CVIBuffer(rhs)
	, m_iVertexCountRow(rhs.m_iVertexCountRow)
	, m_iVertexCountCol(rhs.m_iVertexCountCol)
	, m_iCellSpacing(rhs.m_iCellSpacing)
	, m_iCellCountRow(rhs.m_iCellCountRow)
	, m_iCellCountCol(rhs.m_iCellCountCol)
	, m_iWidth(rhs.m_iWidth)
	, m_iHeight(rhs.m_iHeight)
{
}


CRcTerrain::~CRcTerrain()
{
}

HRESULT CRcTerrain::Ready_Buffer(void)
{
	m_dwFVF = FVF_TEX;

	m_iCellCountRow = m_iVertexCountRow - 1;
	m_iCellCountCol = m_iVertexCountCol - 1;

	m_iWidth = m_iCellCountRow * m_iCellSpacing;
	m_iHeight = m_iCellCountCol * m_iCellSpacing;
	
	m_dwVtxCnt = m_iVertexCountRow * m_iVertexCountCol;
	m_dwTriCnt = m_iCellCountRow * m_iCellCountCol * 2;

	m_dwVtxSize = sizeof(VTXTEX);
	m_dwIdxSize = sizeof(INDEX32);
	m_IdxFmt = D3DFMT_INDEX32;

	FAILED_CHECK_RETURN(CVIBuffer::Ready_Buffer(), E_FAIL);

	VTXTEX*		pVertex = nullptr;

	int iStartX = (int)(-1 * m_iWidth) / 2;
	int iStartZ = (int)(-1 * m_iHeight) / 2;

	int iEndX = m_iWidth / 2;
	int iEndZ = m_iHeight / 2;

	_float fStepCoordU = 1.f / (float)m_iCellCountRow;
	_float fStepCoordV = 1.f / (float)m_iCellCountCol;

	m_pVB->Lock(0, 0, (void**)&pVertex, 0);

	int i = 0;
	for (int z = iStartZ; z <= iEndZ; z += m_iCellSpacing)
	{
		int j = 0;
		for (int x = iStartX; x <= iEndX; x += m_iCellSpacing)
		{
			int idx = i * m_iVertexCountRow + j;

			pVertex[idx].vPosition.x = float(x);
			pVertex[idx].vPosition.y = 0.f;
			pVertex[idx].vPosition.z = float(z);
			
			pVertex[idx].vTexUV.x = (float)j * fStepCoordU;
			pVertex[idx].vTexUV.y = (float)i * fStepCoordV;

			++j;
		}
		++i;
	}
	m_pVB->Unlock();


	// TODO :: 오류 시 여기 살펴볼 것.
	INDEX32*			pIndex = nullptr;

	m_pIB->Lock(0, 0, (void**)&pIndex, 0);

	int baseIdx = 0;

	for (int i = 0; i < m_iCellCountCol; ++i)
	{
		for (int j = 0; j < m_iCellCountRow; ++j)
		{
			INDEX32 indexTri_1 
			{ 
				i * m_iVertexCountRow + j ,
				i * m_iVertexCountRow + j + 1,
				(i + 1) * m_iVertexCountRow + j
			};
			pIndex[baseIdx++] = indexTri_1;

			INDEX32 indexTri_2
			{ 
				(i + 1) * m_iVertexCountRow + j,
				i * m_iVertexCountRow + j + 1,
				(i + 1) * m_iVertexCountRow + j + 1
			};

			m_listIndex.push_back(indexTri_1);
			m_listIndex.push_back(indexTri_2);

			pIndex[baseIdx++] = indexTri_2;
		}
	}

	m_pIB->Unlock();


	return S_OK;
}

void CRcTerrain::Render_Buffer(void)
{
	CVIBuffer::Render_Buffer();
}

CRcTerrain * CRcTerrain::Create(LPDIRECT3DDEVICE9 pGraphicDev, _uint iVertexRow, _uint iVertexCol, _uint iCellSpacing)
{
	CRcTerrain *	pInstance = new CRcTerrain(pGraphicDev);

	pInstance->m_iVertexCountRow = iVertexRow;
	pInstance->m_iVertexCountCol = iVertexCol;
	pInstance->m_iCellSpacing = iCellSpacing;

	if (FAILED(pInstance->Ready_Buffer()))
	{
		Safe_Release(pInstance);
		MSG_BOX("RcTerrain Create Failed");
		return nullptr;
	}

	return pInstance;
}

CComponent * CRcTerrain::Clone(void)
{
	return new CRcTerrain(*this);
}

void CRcTerrain::Free(void)
{
	CVIBuffer::Free();
}
