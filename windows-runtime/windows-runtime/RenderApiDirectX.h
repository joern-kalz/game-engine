#pragma once
#include "RenderApi.h"
class RenderApiDirectX :
    public RenderApi
{
public:
    virtual void Initialize();

private:
    bool IsDebugLayerSupported();
    HRESULT CreateDevice(D3D_DRIVER_TYPE type, UINT flags, winrt::com_ptr<ID3D11Device>* d3d11device,
        winrt::com_ptr<ID3D11DeviceContext>* d3d11context);

    winrt::com_ptr<ID3D11Device3> device_;
    winrt::com_ptr<ID3D11DeviceContext3>  context_;
    D3D_FEATURE_LEVEL supported_feature_level_{};
};

