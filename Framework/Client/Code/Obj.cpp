#include "stdafx.h"
#include "..\Header\Obj.h"


CObj::CObj()
{
	ZeroMemory(&m_vPos, sizeof(_vec3));
	ZeroMemory(&m_vRotation, sizeof(_vec3));
	ZeroMemory(&m_vSize, sizeof(_vec3));
	D3DXMatrixIdentity(&m_matWolrd);
}


CObj::~CObj()
{
}
