#include "pch.h"
#include "DirectXDeviceFactory.h"

DirectXDeviceFactory::DirectXDeviceFactory(std::shared_ptr<DirectXProxy> direct_x_proxy) :
    direct_x_proxy_(direct_x_proxy)
{
}

std::shared_ptr<DirectXDevice> DirectXDeviceFactory::CreateDirectXDevice()
{
    UINT creationFlags = 0;

#if defined(_DEBUG)        
    if (IsDebugLayerSupported()) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
    }
#endif

    CreateDeviceResult result = CreateDevice(D3D_DRIVER_TYPE_HARDWARE, creationFlags);

    if (FAILED(result.hr)) {
        result = CreateDevice(D3D_DRIVER_TYPE_WARP, creationFlags);
        winrt::check_hresult(result.hr);
    }

    return std::make_shared<DirectXDevice>(result.device, result.context, result.feature_level);
}

bool DirectXDeviceFactory::IsDebugLayerSupported()
{
    HRESULT hr = direct_x_proxy_->CreateDevice(
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

DirectXDeviceFactory::CreateDeviceResult DirectXDeviceFactory::CreateDevice(D3D_DRIVER_TYPE type, UINT flags)
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
    CreateDeviceResult result;

    result.hr = direct_x_proxy_->CreateDevice(
        nullptr,
        type,
        0,
        flags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        device.put(),
        &result.feature_level,
        context.put()
    );

    if (SUCCEEDED(result.hr)) {
        result.device = std::make_shared<winrt::com_ptr<ID3D11Device3>>(
            device.as<ID3D11Device3>()
        );
        result.context = std::make_shared<winrt::com_ptr<ID3D11DeviceContext3>>(
            context.as<ID3D11DeviceContext3>()
        );
    }

    return result;
}
