#pragma once

class App
{
public:
	struct PointerEvent { float x; float y; };

	void onPointerPressed(PointerEvent pointerEvent);
	void onPointerMoved(PointerEvent pointerEvent);
	void onPointerReleased(PointerEvent pointerEvent);
};

