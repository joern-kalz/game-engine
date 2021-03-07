#pragma once

#include "GraphicsDeviceContainer.h"

class GraphicsDeviceContainerImpl : public GraphicsDeviceContainer {
public:
    virtual ID3D11Device3* GetDevice() override { return device_.get(); }
    virtual IDXGIDevice3* GetGIDevice() override  { return device_.as<IDXGIDevice3>().get(); }
    virtual ID3D11DeviceContext3* GetContext() override { return context_.get(); }

    virtual void Create() override;
    virtual void Trim() override;

private:
    bool IsDebugLayerSupported();
    HRESULT CreateDevice(D3D_DRIVER_TYPE type, UINT flags);

    winrt::com_ptr<ID3D11Device3> device_;
    winrt::com_ptr<ID3D11DeviceContext3> context_;
    D3D_FEATURE_LEVEL feature_level_{};
};

