#include "pch.h"
#include "AppImpl.h"

AppImpl::AppImpl(View& view) :
	view_(view)
{
}

void AppImpl::OnInitialize()
{
	view_.OnInitialize();
}

void AppImpl::OnSetWindow(winrt::Windows::UI::Core::CoreWindow const* window)
{
	view_.OnSetWindow(window);
}

void AppImpl::OnLoad()
{
	view_.OnLoad();
}

void AppImpl::OnRun()
{
	view_.Paint();
}

void AppImpl::OnSuspending()
{
	view_.OnSuspending();
}

void AppImpl::OnResuming()
{
}

void AppImpl::OnResize()
{
	view_.OnResize();
}

void AppImpl::OnPointerPressed(PointerEvent)
{
}

void AppImpl::OnPointerMoved(PointerEvent)
{
}

void AppImpl::OnPointerReleased(PointerEvent)
{
}
