#include "pch.h"
#include "GraphicsFacade.h"

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

GraphicsFacade::GraphicsFacade(std::shared_ptr<GraphicsLibrary> graphicsLibrary) :
    library_(graphicsLibrary)
{
}

void GraphicsFacade::Initialize()
{
    UINT creationFlags = 0;

#if defined(_DEBUG)        
    if (IsDebugLayerSupported()) {
        creationFlags |= D3D11_CREATE_DEVICE_DEBUG;
    }
#endif

    HRESULT hr = CreateDevice(D3D_DRIVER_TYPE_HARDWARE, creationFlags);

    if (FAILED(hr)) {
        winrt::check_hresult(
            CreateDevice(D3D_DRIVER_TYPE_WARP, creationFlags)
        );
    }
}

void GraphicsFacade::TrimResourcesOnSuspending()
{
    library_->Trim(&device_);
}

void GraphicsFacade::LoadBasicResources(std::function<void()>)
{
}

void GraphicsFacade::LoadTextures(wchar_t const**, std::function<void()>)
{
}

bool GraphicsFacade::IsDebugLayerSupported()
{
    HRESULT hr = library_->CreateDevice(
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

HRESULT GraphicsFacade::CreateDevice(D3D_DRIVER_TYPE type, UINT flags)
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

    HRESULT hr = library_->CreateDevice(
        nullptr,
        type,
        0,
        flags,
        featureLevels,
        ARRAYSIZE(featureLevels),
        D3D11_SDK_VERSION,
        &device,
        &feature_level_,
        &context
    );

    if (SUCCEEDED(hr)) {
        library_->asDevice3(&device, &device_);
        library_->asContext3(&context, &context_);
    }

    return hr;
}

void GraphicsFacade::LoadBasicResourcesInBackground(std::function<void()> callback)
{
    CreateSampler();
    CreateVertexBuffer();

    callback();
}

void GraphicsFacade::CreateSampler()
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
        library_->CreateSamplerState(&device_, &sampDesc, sampler_.put())
    );
}

void GraphicsFacade::CreateVertexBuffer()
{
    D3D11_BUFFER_DESC bd = { 0 };
    bd.ByteWidth = sizeof(VERTEX) * ARRAYSIZE(OurVertices);
    bd.BindFlags = D3D11_BIND_VERTEX_BUFFER;

    D3D11_SUBRESOURCE_DATA srd = { OurVertices, 0, 0 };

    winrt::check_hresult(
        library_->CreateBuffer(&device_, &bd, &srd, m_vertexBuffer.put())
    );
}
