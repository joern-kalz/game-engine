#include "pch.h"
#include "AppAdapter.h"

using namespace winrt::Windows::ApplicationModel;
using namespace winrt::Windows::ApplicationModel::Activation;
using namespace winrt::Windows::ApplicationModel::Core;
using namespace winrt::Windows::Foundation::Numerics;
using namespace winrt::Windows::UI::Core;

AppAdapter::AppAdapter(App& app) :
    app_(app),
    closed_(false),
    visible_(true)
{
}

IFrameworkView AppAdapter::CreateView()
{
    return *this;
}

void AppAdapter::Initialize(CoreApplicationView const& application_view)
{
    application_view.Activated([&](CoreApplicationView const&, IActivatedEventArgs const&) {
        CoreWindow::GetForCurrentThread().Activate();
    });
    CoreApplication::Suspending([&](IInspectable const&, SuspendingEventArgs const& args) -> winrt::fire_and_forget {
        auto lifetime = get_strong();
        SuspendingDeferral deferral = args.SuspendingOperation().GetDeferral();
        co_await winrt::resume_background();
        app_.OnSuspending();
        deferral.Complete();
    });
    CoreApplication::Resuming([&](IInspectable const&, IInspectable const&) {
        app_.OnResuming();
    });

    app_.OnInitialize();
}

void AppAdapter::SetWindow(CoreWindow const& window)
{
    window.PointerPressed([&](IInspectable const&, PointerEventArgs const& args) {
        app_.OnPointerPressed(ConvertToPointerEvent(args));
    });
    window.PointerMoved([&](IInspectable const&, PointerEventArgs const& args) {
        app_.OnPointerMoved(ConvertToPointerEvent(args));
    });
    window.PointerReleased([&](IInspectable const&, PointerEventArgs const& args) {
        app_.OnPointerReleased(ConvertToPointerEvent(args));
    });
    window.SizeChanged([&](CoreWindow const&, WindowSizeChangedEventArgs const&) {
        app_.OnResize();
    });
    window.VisibilityChanged([&](CoreWindow const&, VisibilityChangedEventArgs const& args) {
        visible_ = args.Visible();
    });
    window.Closed([&](CoreWindow const&, CoreWindowEventArgs const&) {
        closed_ = true;
    });
 
    using DisplayInformation = winrt::Windows::Graphics::Display::DisplayInformation;
    DisplayInformation currentDisplayInformation{ DisplayInformation::GetForCurrentView() };

    currentDisplayInformation.DpiChanged([&](DisplayInformation const&, IInspectable const&) {
        app_.OnResize();
    });
    currentDisplayInformation.OrientationChanged([&](DisplayInformation const&, IInspectable const&) {
        app_.OnResize();
    });

    app_.OnSetWindow(&window);
}

void AppAdapter::Load(winrt::hstring const&)
{
    app_.OnLoad();
}

void AppAdapter::Run()
{
    while (!closed_) {
        if (visible_) {
            CoreWindow::GetForCurrentThread().Dispatcher().ProcessEvents(CoreProcessEventsOption::ProcessAllIfPresent);
            app_.OnRun();
        } else {
            CoreWindow::GetForCurrentThread().Dispatcher().ProcessEvents(CoreProcessEventsOption::ProcessOneAndAllPending);
        }
    }
}

void AppAdapter::Uninitialize()
{
}

App::PointerEvent AppAdapter::ConvertToPointerEvent(PointerEventArgs args)
{
    float2 point = args.CurrentPoint().Position();
    return App::PointerEvent{ point.x, point.y };
}
