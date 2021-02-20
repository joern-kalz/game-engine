#pragma once

#include "App.h"

using namespace winrt;

using namespace Windows;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;

class AppAdapter : public implements<AppAdapter, IFrameworkViewSource, IFrameworkView>
{
    App app;

public:
    IFrameworkView CreateView();
    void Initialize(CoreApplicationView const&);
    void Load(hstring const&);
    void Uninitialize();
    void Run();
    void SetWindow(CoreWindow const& window);

private:
    App::PointerEvent convertToPointerEvent(PointerEventArgs args);
};
