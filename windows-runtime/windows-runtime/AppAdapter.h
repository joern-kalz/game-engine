#pragma once

#include <memory>

#include "App.h"

using namespace std;
using namespace winrt;
using namespace Windows;
using namespace Windows::ApplicationModel;
using namespace Windows::ApplicationModel::Activation;
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
    void Initialize(CoreApplicationView const& application_view);
    void SetWindow(CoreWindow const& window);
    void Load(hstring const&);
    void Run();
    void Uninitialize();

private:
    void OnActivated(CoreApplicationView const&, IActivatedEventArgs const&);
    winrt::fire_and_forget OnSuspending(IInspectable const&, SuspendingEventArgs const& args);
    void OnResuming(IInspectable const&, IInspectable const&);

    App::PointerEvent ConvertToPointerEvent(PointerEventArgs args);

    shared_ptr<App> app_;
};
