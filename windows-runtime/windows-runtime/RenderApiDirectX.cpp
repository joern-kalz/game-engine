#include "pch.h"
#include "RenderApiDirectX.h"

void RenderApiDirectX::Initialize()
{
    UINT creationFlags = 0;

#if defined(_DEBUG)        
    if (IsDebugLayerSupported()) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
    }
#endif

    winrt::com_ptr<ID3D11Device> d3d11device;
    winrt::com_ptr<ID3D11DeviceContext> d3d11context;
    
    HRESULT hr = CreateDevice(D3D_DRIVER_TYPE_HARDWARE, creationFlags, &d3d11device, &d3d11context);

    if (FAILED(hr)) {
        winrt::check_hresult(
            CreateDevice(D3D_DRIVER_TYPE_WARP, creationFlags, &d3d11device, &d3d11context)
        );
    }

    device_ = d3d11device.as<ID3D11Device3>();
    context_ = d3d11context.as<ID3D11DeviceContext3>();
}

bool RenderApiDirectX::IsDebugLayerSupported()
{
    HRESULT hr = D3D11CreateDevice(
        nullptr,
        D3D_DRIVER_TYPE_NULL,
        0,
        D3D11_CREATE_DEVICE_DEBUG,
        nullptr,
        0,
        D3D11_SDK_VERSION,
        nullptr,
        nullptr,
        nullptr
    );

    return SUCCEEDED(hr);
}

HRESULT RenderApiDirectX::CreateDevice(D3D_DRIVER_TYPE type, UINT flags, winrt::com_ptr<ID3D11Device>* d3d11device, 
    winrt::com_ptr<ID3D11DeviceContext>* d3d11context)
{
    D3D_FEATURE_LEVEL featureLevels[] =
    {
        D3D_FEATURE_LEVEL_11_1,
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_1,
        D3D_FEATURE_LEVEL_10_0,
        D3D_FEATURE_LEVEL_9_3,
        D3D_FEATURE_LEVEL_9_2,
        D3D_FEATURE_LEVEL_9_1
    };

    return D3D11CreateDevice(
        nullptr,
        type,
        0,
        flags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        d3d11device->put(),
        &supported_feature_level_,
        d3d11context->put()
    );
}
