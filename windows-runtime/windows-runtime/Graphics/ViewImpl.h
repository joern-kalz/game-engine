#pragma once

#include <memory>
#include "View.h"
#include "GraphicsDeviceContainer.h"
#include "DoubleBuffer.h"
#include "Painter.h"

class ViewImpl : public View {
public:
    ViewImpl(
        GraphicsDeviceContainer& device_container,
        DoubleBuffer& double_buffer,
        std::vector<std::shared_ptr<Painter>> painters
    );

    virtual void OnInitialize() override;
    virtual void OnSetWindow(winrt::Windows::UI::Core::CoreWindow const* window) override;
    virtual void OnLoad() override;
    virtual void OnSuspending() override;
    virtual void OnResize() override;

    virtual void Paint() override;

private:
    winrt::fire_and_forget CreatePainterResources();
    void InvokePainters();
    void HandleDeviceLost();

    GraphicsDeviceContainer& device_container_;
    DoubleBuffer& double_buffer_;
    std::vector<std::shared_ptr<Painter>> painters_;

    bool ready_;
};

