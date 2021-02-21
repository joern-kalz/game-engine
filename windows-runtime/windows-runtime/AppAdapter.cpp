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

void AppAdapter::Initialize(CoreApplicationView const&)
{
}

void AppAdapter::Load(hstring const&)
{
}

void AppAdapter::Uninitialize()
{
}

void AppAdapter::Run()
{
    CoreWindow window = CoreWindow::GetForCurrentThread();
    window.Activate();

    CoreDispatcher dispatcher = window.Dispatcher();
    dispatcher.ProcessEvents(CoreProcessEventsOption::ProcessUntilQuit);
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

App::PointerEvent AppAdapter::ConvertToPointerEvent(PointerEventArgs args)
{
    float2 point = args.CurrentPoint().Position();
    return App::PointerEvent{ point.x, point.y };
}
