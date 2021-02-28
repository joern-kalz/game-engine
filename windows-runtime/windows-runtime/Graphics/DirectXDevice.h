#pragma once

#include <functional>
#include <memory>

#include "DirectXProxy.h"

class DirectXDevice {
public:
    DirectXDevice(
        std::shared_ptr<winrt::com_ptr<ID3D11Device3>> device,
        std::shared_ptr<winrt::com_ptr<ID3D11DeviceContext3>> context,
        D3D_FEATURE_LEVEL feature_level
    );

    void TrimResourcesOnSuspending();
    void LoadBasicResources(std::function<void()> callback);
    void LoadTextures(wchar_t const** textures, std::function<void()> callback);

private:
    void LoadBasicResourcesInBackground(std::function<void()> callback);
    void CreateSampler();
    void CreateVertexBuffer();

    std::shared_ptr< winrt::com_ptr<ID3D11Device3>> device_;
    std::shared_ptr< winrt::com_ptr<ID3D11DeviceContext3>> context_;
    D3D_FEATURE_LEVEL feature_level_{};

    winrt::com_ptr<ID3D11SamplerState> sampler_{ nullptr };
    winrt::com_ptr<ID3D11Buffer>  vertex_buffer_;
};

