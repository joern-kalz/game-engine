#pragma once

class View {
public:
    virtual ~View() {}
    virtual void OnInitialize() = 0;
    virtual void OnSetWindow(winrt::Windows::UI::Core::CoreWindow const* window) = 0;
    virtual void OnLoad() = 0;
    virtual void OnSuspending() = 0;
    virtual void OnResize() = 0;

    virtual void Paint() = 0;
};

