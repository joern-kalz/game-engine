#pragma once

#include "GraphicsResourceFactory.h"
#include "GraphicsDeviceProvider.h"
#include "../AssetLoader/AssetLoader.h"

class GraphicsResourceFactoryImpl : public GraphicsResourceFactory {
public:
    GraphicsResourceFactoryImpl(
        GraphicsDeviceProvider& device_provider,
        AssetLoader& asset_loader
    );

    virtual void CreateSamplerState(
        ID3D11SamplerState** sampler_state
    ) override;

    virtual void CreateVertexBuffer(
        ID3D11Buffer** buffer, 
        int size, 
        void* data
    ) override;

    virtual winrt::Windows::Foundation::IAsyncAction CreateTexture(
        winrt::hstring filename,
        ID3D11Texture2D** texture,
        ID3D11ShaderResourceView** resource_view
    ) override;

    virtual winrt::Windows::Foundation::IAsyncAction CreateVertexShader(
        winrt::hstring filename,
        D3D11_INPUT_ELEMENT_DESC const layout_elements[],
        uint32_t layout_elements_count,
        ID3D11VertexShader** shader,
        ID3D11InputLayout** layout
    ) override;

    virtual winrt::Windows::Foundation::IAsyncAction CreatePixelShader(
        _In_ winrt::hstring filename,
        _Out_ ID3D11PixelShader** shader
    ) override;

private:
    GraphicsDeviceProvider& device_provider_;
    AssetLoader& asset_loader_;
};

