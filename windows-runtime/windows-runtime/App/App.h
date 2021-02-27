#pragma once

#include <memory>

#include "../Graphics/DirectXDeviceFactory.h"

using namespace std;

class App
{
public:
	struct PointerEvent { float x; float y; };

	App(shared_ptr<DirectXDeviceFactory> direct_x_device_factory);

	void OnInitialize();
	void OnLoad();
	void OnSuspending();
	void OnResuming();
	void OnPointerPressed(PointerEvent pointer_event);
	void OnPointerMoved(PointerEvent pointer_event);
	void OnPointerReleased(PointerEvent pointer_event);

private:
	shared_ptr<DirectXDeviceFactory> direct_x_device_factory_;
	shared_ptr<DirectXDevice> direct_x_device_;
	bool resources_loaded_;
	bool textures_loaded_;
};

