#pragma once

#include <memory>
#include "GraphicsDeviceProvider.h"

class GraphicsResourceFactory {
public:
    virtual ~GraphicsResourceFactory() {}

    virtual void CreateSamplerState(
        ID3D11SamplerState** sampler_state
    ) = 0;

    virtual void CreateVertexBuffer(
        ID3D11Buffer** buffer,
        int size,
        void* data
    ) = 0;

    virtual winrt::Windows::Foundation::IAsyncAction CreateTexture(
        winrt::hstring filename,
        ID3D11Texture2D** texture,
        ID3D11ShaderResourceView** resource_view
    ) = 0;

    virtual winrt::Windows::Foundation::IAsyncAction CreateVertexShader(
        winrt::hstring filename,
        D3D11_INPUT_ELEMENT_DESC const layout_elements[],
        uint32_t layout_elements_count,
        ID3D11VertexShader** shader,
        ID3D11InputLayout** layout
    ) = 0;

    virtual winrt::Windows::Foundation::IAsyncAction CreatePixelShader(
        _In_ winrt::hstring filename,
        _Out_ ID3D11PixelShader** shader
    ) = 0;

};

