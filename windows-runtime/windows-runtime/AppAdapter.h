#pragma once

#include <memory>

#include "App.h"

using namespace std;
using namespace winrt;
using namespace Windows;
using namespace Windows::ApplicationModel::Core;
using namespace Windows::Foundation::Numerics;
using namespace Windows::UI;
using namespace Windows::UI::Core;
using namespace Windows::UI::Composition;

class AppAdapter : public implements<AppAdapter, IFrameworkViewSource, IFrameworkView>
{
public:
    AppAdapter(shared_ptr<App> app);

    IFrameworkView CreateView();
    void Initialize(CoreApplicationView const&);
    void Load(hstring const&);
    void Uninitialize();
    void Run();
    void SetWindow(CoreWindow const& window);

private:
    App::PointerEvent ConvertToPointerEvent(PointerEventArgs args);

    shared_ptr<App> app_;
};
