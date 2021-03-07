#pragma once

class App
{
public:
	struct PointerEvent { float x; float y; };

	virtual ~App() {}

	virtual void OnInitialize() = 0;
	virtual void OnSetWindow(winrt::Windows::UI::Core::CoreWindow const* window) = 0;
	virtual void OnLoad() = 0;
	virtual void OnRun() = 0;

	virtual void OnSuspending() = 0;
	virtual void OnResuming() = 0;

	virtual void OnResize() = 0;
	virtual void OnPointerPressed(PointerEvent pointer_event) = 0;
	virtual void OnPointerMoved(PointerEvent pointer_event) = 0;
	virtual void OnPointerReleased(PointerEvent pointer_event) = 0;
};

