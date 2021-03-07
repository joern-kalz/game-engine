#include "pch.h"
#include "GraphicsDeviceContainerImpl.h"

void GraphicsDeviceContainerImpl::Create()
{
    UINT creationFlags = 0;

#if defined(_DEBUG)        
    if (IsDebugLayerSupported()) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
    }
#endif

    HRESULT hr = CreateDevice(D3D_DRIVER_TYPE_HARDWARE, creationFlags);

    if (FAILED(hr)) {
        winrt::check_hresult(CreateDevice(D3D_DRIVER_TYPE_WARP, creationFlags));
    }
}

void GraphicsDeviceContainerImpl::Trim()
{
    device_.as<IDXGIDevice3>()->Trim();
}

bool GraphicsDeviceContainerImpl::IsDebugLayerSupported()
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

HRESULT GraphicsDeviceContainerImpl::CreateDevice(D3D_DRIVER_TYPE type, UINT flags)
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

    winrt::com_ptr<ID3D11Device> device;
    winrt::com_ptr<ID3D11DeviceContext> context;

    HRESULT hr = D3D11CreateDevice(
        nullptr,
        type,
        0,
        flags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        device.put(),
        &feature_level_,
        context.put()
    );

    if (SUCCEEDED(hr)) {
        device_ = device.as<ID3D11Device3>();
        context_ = context.as<ID3D11DeviceContext3>();
    }

    return hr;
}
