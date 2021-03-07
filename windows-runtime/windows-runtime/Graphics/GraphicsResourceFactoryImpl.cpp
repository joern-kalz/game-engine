#include "pch.h"
#include "GraphicsResourceFactoryImpl.h"

GraphicsResourceFactoryImpl::GraphicsResourceFactoryImpl(
    GraphicsDeviceProvider& device_provider,
    AssetLoader& asset_loader
) :
    device_provider_(device_provider),
    asset_loader_(asset_loader)
{
}

void GraphicsResourceFactoryImpl::CreateSamplerState(ID3D11SamplerState** sampler_state)
{
    D3D11_SAMPLER_DESC sampDesc;
    ZeroMemory(&sampDesc, sizeof(sampDesc));

    sampDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_LINEAR;
    sampDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
    sampDesc.ComparisonFunc = D3D11_COMPARISON_NEVER;
    sampDesc.MinLOD = 0;
    sampDesc.MaxLOD = FLT_MAX;

    winrt::check_hresult(
        device_provider_.GetDevice()->CreateSamplerState(&sampDesc, sampler_state)
    );
}

void GraphicsResourceFactoryImpl::CreateVertexBuffer(ID3D11Buffer** buffer, int size, void* data)
{
    D3D11_BUFFER_DESC bd = { 0 };
    bd.ByteWidth = size;
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA srd = { data, 0, 0 };

    winrt::check_hresult(
        device_provider_.GetDevice()->CreateBuffer(&bd, &srd, buffer)
    );
}

winrt::Windows::Foundation::IAsyncAction GraphicsResourceFactoryImpl::CreateTexture(
    winrt::hstring filename, 
    ID3D11Texture2D** texture,
    ID3D11ShaderResourceView** resource_view
)
{
    AssetLoader::Image image;
    co_await asset_loader_.LoadImage(filename, &image);

    D3D11_SUBRESOURCE_DATA initialData {};
    initialData.pSysMem = image.data.get();
    initialData.SysMemPitch = image.width * 4;
    initialData.SysMemSlicePitch = 0;

    CD3D11_TEXTURE2D_DESC textureDesc(
        DXGI_FORMAT_B8G8R8A8_UNORM,
        image.width,
        image.height,
        1,
        1
    );

    winrt::com_ptr<ID3D11Texture2D> texture2D;
    winrt::check_hresult(
        device_provider_.GetDevice()->CreateTexture2D(
            &textureDesc,
            &initialData,
            texture2D.put()
        )
    );

    winrt::com_ptr<ID3D11ShaderResourceView> shaderResourceView;
    if (resource_view != nullptr)
    {
        CD3D11_SHADER_RESOURCE_VIEW_DESC shaderResourceViewDesc(
            texture2D.get(),
            D3D11_SRV_DIMENSION_TEXTURE2D
        );

        winrt::check_hresult(
            device_provider_.GetDevice()->CreateShaderResourceView(
                texture2D.get(),
                &shaderResourceViewDesc,
                shaderResourceView.put()
            )
        );
    }

    if (texture != nullptr)
    {
        *texture = texture2D.detach();
    }
    if (resource_view != nullptr)
    {
        *resource_view = shaderResourceView.detach();
    }
}

winrt::Windows::Foundation::IAsyncAction GraphicsResourceFactoryImpl::CreateVertexShader(
    winrt::hstring filename,
    D3D11_INPUT_ELEMENT_DESC const layout_elements[],
    uint32_t layout_elements_count,
    ID3D11VertexShader** shader,
    ID3D11InputLayout** layout
)
{
    AssetLoader::IBuffer bytecode;
    co_await asset_loader_.LoadBuffer(filename, &bytecode);

    winrt::check_hresult(
        device_provider_.GetDevice()->CreateVertexShader(
            bytecode.data(),
            bytecode.Length(),
            nullptr,
            shader
        )
    );

    winrt::check_hresult(
        device_provider_.GetDevice()->CreateInputLayout(
            layout_elements,
            layout_elements_count,
            bytecode.data(),
            bytecode.Length(),
            layout
        )
    );
}

winrt::Windows::Foundation::IAsyncAction GraphicsResourceFactoryImpl::CreatePixelShader(
    _In_ winrt::hstring filename,
    _Out_ ID3D11PixelShader** shader
)
{
    AssetLoader::IBuffer bytecode;
    co_await asset_loader_.LoadBuffer(filename, &bytecode);

    winrt::check_hresult(
        device_provider_.GetDevice()->CreatePixelShader(
            bytecode.data(),
            bytecode.Length(),
            nullptr,
            shader
        )
    );
}
