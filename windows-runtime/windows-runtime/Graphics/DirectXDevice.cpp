#include "pch.h"
#include "DirectXDevice.h"

struct VERTEX
{
    float X, Y, Z;    // vertex position
    float U, V;
};

VERTEX OurVertices[] =
{
    { 0.0f, 0.5f, 0.0f, 0.5f, 1.0f },
    { 0.45f, -0.5f, 0.0f, 1.0f, 0.0f },
    { -0.45f, -0.5f, 0.0f, 0.0f, 0.0f },
};

DirectXDevice::DirectXDevice(
    std::shared_ptr<winrt::com_ptr<ID3D11Device3>> device, 
    std::shared_ptr<winrt::com_ptr<ID3D11DeviceContext3>> context,
    D3D_FEATURE_LEVEL feature_level
) :
    device_(device),
    context_(context),
    feature_level_(feature_level)
{
}

void DirectXDevice::TrimResourcesOnSuspending()
{
    device_->as<IDXGIDevice3>()->Trim();
}

void DirectXDevice::LoadBasicResources(std::function<void()>)
{
    CreateSampler();
}

void DirectXDevice::LoadTextures(wchar_t const**, std::function<void()>)
{
}

void DirectXDevice::LoadBasicResourcesInBackground(std::function<void()> callback)
{
    CreateSampler();
    CreateVertexBuffer();

    callback();
}

void DirectXDevice::CreateSampler()
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

    //winrt::check_hresult(
    (*device_)->CreateSamplerState(&sampDesc, sampler_.put());
    //);
}

void DirectXDevice::CreateVertexBuffer()
{
    D3D11_BUFFER_DESC bd = { 0 };
    bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(OurVertices);
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA srd = { OurVertices, 0, 0 };

    winrt::check_hresult(
        (*device_)->CreateBuffer(&bd, &srd, vertex_buffer_.put())
    );
}
