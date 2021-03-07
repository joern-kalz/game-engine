#include "pch.h"
#include "DoubleBufferImpl.h"

DoubleBufferImpl::DoubleBufferImpl(GraphicsDeviceProvider& device_provider) :
    device_provider_(device_provider)
{
}

void DoubleBufferImpl::SetWindow(winrt::Windows::UI::Core::CoreWindow const* window)
{
    window_ = *window;
}

bool DoubleBufferImpl::Create()
{
    float dpi = winrt::Windows::Graphics::Display::DisplayInformation::GetForCurrentView().LogicalDpi();
    Size size{
        max(1, ConvertDipsToPixels(window_.get().Bounds().Width, dpi)),
        max(1, ConvertDipsToPixels(window_.get().Bounds().Height, dpi))
    };

    ID3D11RenderTargetView* nullViews[] = { nullptr };
    device_provider_.GetContext()->OMSetRenderTargets(ARRAYSIZE(nullViews), nullViews, nullptr);
    render_target_view_ = nullptr;
    depth_stencil_view_ = nullptr;
    device_provider_.GetContext()->Flush();

    if (swap_chain_ == nullptr) {
        CreateSwapChain(size);
    } else {
        bool success = AdjustSwapChain(size);

        if (!success) {
            return false;
        }
    }

    CreateRenderTargetView();
    CreateDepthStencilView(size);
    InitializeViewport(size);

    return true;
}

void DoubleBufferImpl::Destroy()
{
    swap_chain_ = nullptr;

    device_provider_.GetContext()->OMSetRenderTargets(0, nullptr, nullptr);
    depth_stencil_view_ = nullptr;
    render_target_view_ = nullptr;
    device_provider_.GetContext()->Flush();
}

void DoubleBufferImpl::StartFrame()
{
    ID3D11RenderTargetView* const targets[1] = { render_target_view_.get() };
    device_provider_.GetContext()->OMSetRenderTargets(1, targets, nullptr);

    device_provider_.GetContext()->ClearDepthStencilView(depth_stencil_view_.get(), D3D11_CLEAR_DEPTH, 1.0f, 0);

    const float clearColor[4] = { 0.0f, 1.0f, 0.0f, 1.0f };
    device_provider_.GetContext()->ClearRenderTargetView(render_target_view_.get(), clearColor);
}

bool DoubleBufferImpl::FinishFrame()
{
    HRESULT hr = swap_chain_->Present(1, 0);
    device_provider_.GetContext()->DiscardView(render_target_view_.get());
    device_provider_.GetContext()->DiscardView(depth_stencil_view_.get());

    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
        return false;
    }

    winrt::check_hresult(hr);
    return true;
}

void DoubleBufferImpl::CreateSwapChain(Size size)
{
    DXGI_SWAP_CHAIN_DESC1 swapChainDesc = { 0 };

    swapChainDesc.Width = static_cast<UINT>(size.width);
    swapChainDesc.Height = static_cast<UINT>(size.height);
    swapChainDesc.Format = DXGI_FORMAT_B8G8R8A8_UNORM;
    swapChainDesc.Stereo = false;
    swapChainDesc.SampleDesc.Count = 1;
    swapChainDesc.SampleDesc.Quality = 0;
    swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDesc.BufferCount = 2;
    swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL;
    swapChainDesc.Flags = 0;
    swapChainDesc.Scaling = DXGI_SCALING_NONE;
    swapChainDesc.AlphaMode = DXGI_ALPHA_MODE_IGNORE;

    IDXGIDevice3* dxgiDevice = device_provider_.GetGIDevice();

    winrt::com_ptr<IDXGIAdapter> dxgiAdapter;
    winrt::check_hresult(
        dxgiDevice->GetAdapter(dxgiAdapter.put())
    );

    winrt::com_ptr<IDXGIFactory3> dxgiFactory;
    winrt::check_hresult(
        dxgiAdapter->GetParent(IID_PPV_ARGS(&dxgiFactory))
    );

    winrt::check_hresult(
        dxgiFactory->CreateSwapChainForCoreWindow(
            device_provider_.GetDevice(),
            winrt::get_unknown(window_.get()),
            &swapChainDesc,
            nullptr,
            swap_chain_.put()
        )
    );

    winrt::check_hresult(
        dxgiDevice->SetMaximumFrameLatency(1)
    );
}

bool DoubleBufferImpl::AdjustSwapChain(Size size)
{
    HRESULT hr = swap_chain_->ResizeBuffers(
        2,
        static_cast<UINT>(size.width),
        static_cast<UINT>(size.height),
        DXGI_FORMAT_B8G8R8A8_UNORM,
        0
    );

    if (hr == DXGI_ERROR_DEVICE_REMOVED || hr == DXGI_ERROR_DEVICE_RESET) {
        return false;
    }

    winrt::check_hresult(hr);
    return true;
}

void DoubleBufferImpl::CreateRenderTargetView()
{
    winrt::com_ptr<ID3D11Texture2D> backBuffer = winrt::capture<ID3D11Texture2D>(swap_chain_, &IDXGISwapChain1::GetBuffer, 0);

    winrt::check_hresult(
        device_provider_.GetDevice()->CreateRenderTargetView(
            backBuffer.get(),
            nullptr,
            render_target_view_.put()
        )
    );
}

void DoubleBufferImpl::CreateDepthStencilView(Size size)
{
    CD3D11_TEXTURE2D_DESC depthStencilDesc(
        DXGI_FORMAT_D24_UNORM_S8_UINT,
        static_cast<UINT>(size.width),
        static_cast<UINT>(size.height),
        1,
        1,
        D3D11_BIND_DEPTH_STENCIL
    );

    winrt::com_ptr<ID3D11Texture2D> depthStencil;
    winrt::check_hresult(
        device_provider_.GetDevice()->CreateTexture2D(
            &depthStencilDesc,
            nullptr,
            depthStencil.put()
        )
    );

    CD3D11_DEPTH_STENCIL_VIEW_DESC depthStencilViewDesc(D3D11_DSV_DIMENSION_TEXTURE2D);
    winrt::check_hresult(
        device_provider_.GetDevice()->CreateDepthStencilView(
            depthStencil.get(),
            &depthStencilViewDesc,
            depth_stencil_view_.put()
        )
    );
}

void DoubleBufferImpl::InitializeViewport(Size size)
{
    D3D11_VIEWPORT m_screenViewport = CD3D11_VIEWPORT(
        0.0f,
        0.0f,
        size.width,
        size.height
    );

    device_provider_.GetContext()->RSSetViewports(1, &m_screenViewport);
}
