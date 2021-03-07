#pragma once

#include "App.h"
#include "../Graphics/View.h"

class AppImpl : public App {
public:
	AppImpl(View& view);

	virtual void OnInitialize() override;
	virtual void OnSetWindow(winrt::Windows::UI::Core::CoreWindow const* window) override;
	virtual void OnLoad() override;
	virtual void OnRun() override;

	virtual void OnSuspending() override;
	virtual void OnResuming() override;

	virtual void OnResize() override;
	virtual void OnPointerPressed(PointerEvent pointer_event) override;
	virtual void OnPointerMoved(PointerEvent pointer_event) override;
	virtual void OnPointerReleased(PointerEvent pointer_event) override;

private:
	View& view_;
};

