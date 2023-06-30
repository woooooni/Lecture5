#include "..\..\Header\Light.h"
#include "Export_Function.h"

CLight::CLight(LPDIRECT3DDEVICE9 _pDevice)
    : m_pDevice(_pDevice)
    , m_iIndex(0)
{
    ZeroMemory(&m_tLightInfo, sizeof(D3DLIGHT9));
    m_pDevice->AddRef();
}

CLight::~CLight()
{
}

HRESULT CLight::Ready_Light(const D3DLIGHT9* pLight, const _uint& iIndex)
{
    memcpy(&m_tLightInfo, pLight, sizeof(D3DLIGHT9));

    m_iIndex = iIndex;

    m_pDevice->SetLight(iIndex, pLight);
    m_pDevice->LightEnable(iIndex, TRUE);

    return S_OK;
}

CLight* CLight::Create(LPDIRECT3DDEVICE9 _pDevice, const D3DLIGHT9* pLightInfo, const _uint& iIndex)
{
    CLight* pInstance = new CLight(_pDevice);

    if (FAILED(pInstance->Ready_Light(pLightInfo, iIndex)))
    {
        Safe_Release(pInstance);
        MSG_BOX("Light Create Failed");
        return nullptr;
    }

    return pInstance;
}

void CLight::Free()
{
    m_pDevice->LightEnable(m_iIndex, FALSE);
    Safe_Release(m_pDevice);
}
