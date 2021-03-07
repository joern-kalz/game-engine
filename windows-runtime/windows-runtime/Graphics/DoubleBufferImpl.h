#pragma once

#include "DoubleBuffer.h"
#include "GraphicsDeviceProvider.h"

class DoubleBufferImpl : public DoubleBuffer {
public:
    DoubleBufferImpl(GraphicsDeviceProvider& device_provider);

    virtual void SetWindow(winrt::Windows::UI::Core::CoreWindow const* window) override;

    virtual bool Create() override;
    virtual void Destroy() override;
    
    virtual void StartFrame() override;
    virtual bool FinishFrame() override;

private:
    struct Size { float width; float height; };

    float ConvertDipsToPixels(float dips, float dpi) { return floorf(dips * dpi / 96.0f + 0.5f); }

    void CreateSwapChain(Size size);
    bool AdjustSwapChain(Size size);
    void CreateRenderTargetView();
    void CreateDepthStencilView(Size size);
    void InitializeViewport(Size size);

    GraphicsDeviceProvider& device_provider_;
    winrt::agile_ref<winrt::Windows::UI::Core::CoreWindow> window_{ nullptr };
    winrt::com_ptr<ID3D11RenderTargetView> render_target_view_;
    winrt::com_ptr<ID3D11DepthStencilView> depth_stencil_view_;
    winrt::com_ptr<IDXGISwapChain1> swap_chain_;
};

