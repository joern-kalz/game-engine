#pragma once

#include <memory>

#include "RenderApi.h"

using namespace std;

class App
{
public:
	struct PointerEvent { float x; float y; };

	App(shared_ptr<RenderApi> render_api);

	void OnInitialize();
	void OnSuspending();
	void OnResuming();
	void OnPointerPressed(PointerEvent pointer_event);
	void OnPointerMoved(PointerEvent pointer_event);
	void OnPointerReleased(PointerEvent pointer_event);

private:
	shared_ptr<RenderApi> render_api_;
};

