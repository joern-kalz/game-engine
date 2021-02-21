#include "pch.h"

#include "../windows-runtime/App.h"

TEST(AppTest, shouldNotThrowWhenPointerMoved) {
	App app;
	app.onPointerMoved(App::PointerEvent{ 0, 0 });
}