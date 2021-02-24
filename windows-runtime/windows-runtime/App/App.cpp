#include "pch.h"
#include "App.h"

App::App(shared_ptr<GraphicsFacade> graphics_facade) : 
	graphics_facade_(graphics_facade),
	resources_loaded_(false),
	textures_loaded_(false)
{
}

void App::OnInitialize()
{
	graphics_facade_->Initialize();
}

void App::OnLoad()
{
	graphics_facade_->LoadBasicResources([&]() { resources_loaded_ = true; });
}

void App::OnSuspending()
{
	graphics_facade_->TrimResourcesOnSuspending();
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
