#pragma once

#include <functional>
#include <memory>

#include "GraphicsLibrary.h"

class GraphicsFacade {
public:
    GraphicsFacade(std::shared_ptr<GraphicsLibrary> graphicsLibrary);
    void Initialize();
    void TrimResourcesOnSuspending();
    void LoadBasicResources(std::function<void()> callback);
    void LoadTextures(wchar_t const** textures, std::function<void()> callback);

private:
    bool IsDebugLayerSupported();
    HRESULT CreateDevice(D3D_DRIVER_TYPE type, UINT flags);
    void LoadBasicResourcesInBackground(std::function<void()> callback);
    void CreateSampler();
    void CreateVertexBuffer();

    std::shared_ptr<GraphicsLibrary> library_;

    winrt::com_ptr<ID3D11Device3> device_;
    D3D_FEATURE_LEVEL feature_level_{};
    winrt::com_ptr<ID3D11DeviceContext3> context_;

    winrt::com_ptr<ID3D11SamplerState> sampler_{ nullptr };
    winrt::com_ptr<ID3D11Buffer>  m_vertexBuffer;
};

