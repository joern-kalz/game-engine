#pragma once

#include "DirectXProxyMock.h"
#include "../../windows-runtime/App/App.h"

struct AppTestSetup {
	shared_ptr<DirectXProxyMock> direct_x_proxy = make_shared<DirectXProxyMock>();
	shared_ptr<DirectXDeviceFactory> direct_x_device_factory = make_shared<DirectXDeviceFactory>(direct_x_proxy);
	shared_ptr<App> app = make_shared<App>(direct_x_device_factory);
};

#define EXPECT_CHECK_DEBUG_LAYER_SUPPORT(library) \
	EXPECT_CALL(*(library), CreateDevice(_, D3D_DRIVER_TYPE_NULL, _, _, _, _, _, _, _, _))

#define EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(library) \
	EXPECT_CALL(*(library), CreateDevice(_, D3D_DRIVER_TYPE_HARDWARE, _, _, _, _, _, _, _, _))

#define EXPECT_CREATE_FALLBACK_DEVICE(library) \
	EXPECT_CALL(*(library), CreateDevice(_, D3D_DRIVER_TYPE_WARP, _, _, _, _, _, _, _, _))
