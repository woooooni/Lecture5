CComponent*			Get_Component(const _tchar* pLayerTag,
									const _tchar* pObjTag,
									const _tchar* pComponentTag,
									COMPONENTID eID)
{
	return CManagement::GetInstance()->Get_Component(pLayerTag, pObjTag, pComponentTag, eID);
}

HRESULT		Create_Management(LPDIRECT3DDEVICE9 pGraphicDev, CManagement** ppInstance)
{
	CManagement*		pManagement = CManagement::GetInstance();
	NULL_CHECK_RETURN(pManagement, E_FAIL);

	*ppInstance = pManagement;

	return S_OK;
}

HRESULT		Set_Scene(CScene* pScene)
{
	return CManagement::GetInstance()->Set_Scene(pScene);
}
_int			Update_Scene(const _float& fTimeDelta)
{
	return CManagement::GetInstance()->Update_Scene(fTimeDelta);
}
void			LateUpdate_Scene()
{
	CManagement::GetInstance()->LateUpdate_Scene();
}
void			Render_Scene(LPDIRECT3DDEVICE9 pGraphicDev)
{
	CManagement::GetInstance()->Render_Scene(pGraphicDev);
}

void			Release_Utility()
{
	CManagement::GetInstance()->DestroyInstance();
}