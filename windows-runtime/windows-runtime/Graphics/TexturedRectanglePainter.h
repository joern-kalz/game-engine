#pragma once

#include <memory>
#include "Painter.h"
#include "GraphicsDeviceProvider.h"
#include "GraphicsResourceFactory.h"

class TexturedRectanglePainter : public Painter {
public:
    TexturedRectanglePainter(
        GraphicsDeviceProvider& device_provider,
        GraphicsResourceFactory& resource_factory
    );
    virtual winrt::Windows::Foundation::IAsyncAction CreateResources() override;
    virtual void Paint() override;

private:
    GraphicsDeviceProvider& device_provider_;
    GraphicsResourceFactory& resource_factory_;

    winrt::com_ptr<ID3D11VertexShader> vertex_shader_;
    winrt::com_ptr<ID3D11PixelShader> pixel_shader_;
    winrt::com_ptr<ID3D11InputLayout> input_layout_;
    winrt::com_ptr<ID3D11SamplerState> sampler_state_;
    winrt::com_ptr<ID3D11Buffer> vertex_buffer_;
    winrt::com_ptr<ID3D11ShaderResourceView> texture_;
};

