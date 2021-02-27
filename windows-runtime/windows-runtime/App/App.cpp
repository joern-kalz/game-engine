#include "pch.h"
#include "App.h"

App::App(shared_ptr<DirectXDeviceFactory> direct_x_device_factory) : 
	direct_x_device_factory_(direct_x_device_factory),
	resources_loaded_(false),
	textures_loaded_(false)
{
}

void App::OnInitialize()
{
	direct_x_device_ = direct_x_device_factory_->CreateDirectXDevice();
}

void App::OnLoad()
{
	direct_x_device_->LoadBasicResources([&]() { resources_loaded_ = true; });
}

void App::OnSuspending()
{
	direct_x_device_->TrimResourcesOnSuspending();
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
