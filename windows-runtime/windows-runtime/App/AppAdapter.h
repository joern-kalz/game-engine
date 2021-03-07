#pragma once

#include "App.h"

class AppAdapter : 
    public winrt::implements<
        AppAdapter, 
        winrt::Windows::ApplicationModel::Core::IFrameworkViewSource, 
        winrt::Windows::ApplicationModel::Core::IFrameworkView
    > 
{
public:
    AppAdapter(App& app);

    winrt::Windows::ApplicationModel::Core::IFrameworkView CreateView();
    void Initialize(winrt::Windows::ApplicationModel::Core::CoreApplicationView const& application_view);
    void SetWindow(winrt::Windows::UI::Core::CoreWindow const& window);
    void Load(winrt::hstring const&);
    void Run();
    void Uninitialize();

private:
    App::PointerEvent ConvertToPointerEvent(winrt::Windows::UI::Core::PointerEventArgs args);

    App& app_;
    bool closed_;
    bool visible_;
};
