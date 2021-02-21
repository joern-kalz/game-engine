#include "pch.h"
#include "AppAdapter.h"

AppAdapter::AppAdapter(shared_ptr<App> app) :
    app_(app)
{
}

IFrameworkView AppAdapter::CreateView()
{
    return *this;
}

void AppAdapter::Initialize(CoreApplicationView const& application_view)
{
    application_view.Activated({ this, &AppAdapter::OnActivated });
    CoreApplication::Suspending({ this, &AppAdapter::OnSuspending });
    CoreApplication::Resuming({ this, &AppAdapter::OnResuming });

    app_->OnInitialize();
}

void AppAdapter::SetWindow(CoreWindow const& window)
{
    window.PointerReleased([&](IInspectable const&, PointerEventArgs const& args) {
        app_->OnPointerReleased(ConvertToPointerEvent(args));
    });
    window.PointerMoved([&](IInspectable const&, PointerEventArgs const& args) {
        app_->OnPointerMoved(ConvertToPointerEvent(args));
    });
    window.PointerReleased([&](IInspectable const&, PointerEventArgs const& args) {
        app_->OnPointerReleased(ConvertToPointerEvent(args));
    });
}

void AppAdapter::Load(hstring const&)
{
}

void AppAdapter::Run()
{
    CoreWindow window = CoreWindow::GetForCurrentThread();
    CoreDispatcher dispatcher = window.Dispatcher();
    dispatcher.ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
}

void AppAdapter::Uninitialize()
{
}

void AppAdapter::OnActivated(CoreApplicationView const&, IActivatedEventArgs const&)
{
    CoreWindow window = CoreWindow::GetForCurrentThread();
    window.Activate();
}

winrt::fire_and_forget AppAdapter::OnSuspending(IInspectable const&, SuspendingEventArgs const& args)
{
    auto lifetime = get_strong();
    SuspendingDeferral deferral = args.SuspendingOperation().GetDeferral();
    co_await winrt::resume_background();

    app_->OnSuspending();

    deferral.Complete();
}

void AppAdapter::OnResuming(IInspectable const&, IInspectable const&)
{
}

App::PointerEvent AppAdapter::ConvertToPointerEvent(PointerEventArgs args)
{
    float2 point = args.CurrentPoint().Position();
    return App::PointerEvent{ point.x, point.y };
}
