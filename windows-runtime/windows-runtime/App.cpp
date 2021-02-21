#include "pch.h"
#include "App.h"

App::App(shared_ptr<RenderApi> render_api) :
	render_api_(render_api)
{
}

void App::OnInitialize()
{
	render_api_->Initialize();
}

void App::OnSuspending()
{
	render_api_->TrimResourcesOnSuspending();
}

void App::OnResuming()
{
}

void App::OnPointerPressed(PointerEvent)
{
}

void App::OnPointerMoved(PointerEvent)
{
}

void App::OnPointerReleased(PointerEvent)
{
}
