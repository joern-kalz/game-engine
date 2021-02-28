#pragma once

#include <functional>
#include <memory>

#include "DirectXProxy.h"
#include "DirectXDeviceFactory.h"

class DirectXDeviceFactoryImpl : public DirectXDeviceFactory {
public:
    DirectXDeviceFactoryImpl(std::shared_ptr<DirectXProxy> direct_x_proxy);
    virtual std::shared_ptr<DirectXDevice> CreateDirectXDevice() override;

private:
    struct CreateDeviceResult {
        HRESULT hr;
        std::shared_ptr<winrt::com_ptr<ID3D11Device3>> device;
        std::shared_ptr<winrt::com_ptr<ID3D11DeviceContext3>> context;
        D3D_FEATURE_LEVEL feature_level;
    };

    bool IsDebugLayerSupported();
    CreateDeviceResult CreateDevice(D3D_DRIVER_TYPE type, UINT flags);

    std::shared_ptr<DirectXProxy> direct_x_proxy_;
};

