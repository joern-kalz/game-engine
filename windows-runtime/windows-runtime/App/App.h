#pragma once

#include <memory>

#include "../Graphics/GraphicsFacade.h"

using namespace std;

class App
{
public:
	struct PointerEvent { float x; float y; };

	App(shared_ptr<GraphicsFacade> graphics_facade);

	void OnInitialize();
	void OnLoad();
	void OnSuspending();
	void OnResuming();
	void OnPointerPressed(PointerEvent pointer_event);
	void OnPointerMoved(PointerEvent pointer_event);
	void OnPointerReleased(PointerEvent pointer_event);

private:
	shared_ptr<GraphicsFacade> graphics_facade_;
	bool resources_loaded_;
	bool textures_loaded_;
};

