#pragma once

#include "GraphicsLibraryMock.h"
#include "../../windows-runtime/App/App.h"

struct AppTestSetup {
	shared_ptr<GraphicsLibraryMock> graphicsLibrary = make_shared<GraphicsLibraryMock>();
	shared_ptr<GraphicsFacade> graphicsFacade = make_shared<GraphicsFacade>(graphicsLibrary);
	shared_ptr<App> app = make_shared<App>(graphicsFacade);
};

#define EXPECT_CHECK_DEBUG_LAYER_SUPPORT(library) \
	EXPECT_CALL(*(library), CreateDevice(_, D3D_DRIVER_TYPE_NULL, _, _, _, _, _, _, _, _))

#define EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(library) \
	EXPECT_CALL(*(library), CreateDevice(_, D3D_DRIVER_TYPE_HARDWARE, _, _, _, _, _, _, _, _))

#define EXPECT_CREATE_FALLBACK_DEVICE(library) \
	EXPECT_CALL(*(library), CreateDevice(_, D3D_DRIVER_TYPE_WARP, _, _, _, _, _, _, _, _))
