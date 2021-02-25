#pragma once

#include "DirectXFactoryMock.h"
#include "../../windows-runtime/App/App.h"

struct AppTestSetup {
	shared_ptr<DirectXFactoryMock> direct_x_factory = make_shared<DirectXFactoryMock>();
	shared_ptr<GraphicsFacade> graphicsFacade = make_shared<GraphicsFacade>(direct_x_factory);
	shared_ptr<App> app = make_shared<App>(graphicsFacade);
};

#define EXPECT_CHECK_DEBUG_LAYER_SUPPORT(library) \
	EXPECT_CALL(*(library), CreateDevice(_, D3D_DRIVER_TYPE_NULL, _, _, _, _, _, _, _, _))

#define EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(library) \
	EXPECT_CALL(*(library), CreateDevice(_, D3D_DRIVER_TYPE_HARDWARE, _, _, _, _, _, _, _, _))

#define EXPECT_CREATE_FALLBACK_DEVICE(library) \
	EXPECT_CALL(*(library), CreateDevice(_, D3D_DRIVER_TYPE_WARP, _, _, _, _, _, _, _, _))
