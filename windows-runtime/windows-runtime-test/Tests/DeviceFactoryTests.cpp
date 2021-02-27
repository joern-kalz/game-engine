#include "pch.h"

#include "DirectXProxyMock.h"
#include "../../windows-runtime/Graphics/DirectXDeviceFactory.h"

using ::testing::_;
using ::testing::AtMost;
using ::testing::Return;

struct DeviceFactoryTestSetup {
	std::shared_ptr<DirectXProxyMock> direct_x_proxy = std::make_shared<DirectXProxyMock>();
	std::shared_ptr<DirectXDeviceFactory> direct_x_device_factory = std::make_shared<DirectXDeviceFactory>(direct_x_proxy);
};

#define EXPECT_CHECK_DEBUG_LAYER_SUPPORT(direct_x_proxy) \
	EXPECT_CALL(*(direct_x_proxy), CreateDevice(_, D3D_DRIVER_TYPE_NULL, _, _, _, _, _, _, _, _))

#define EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(direct_x_proxy) \
	EXPECT_CALL(*(direct_x_proxy), CreateDevice(_, D3D_DRIVER_TYPE_HARDWARE, _, _, _, _, _, _, _, _))

#define EXPECT_CREATE_FALLBACK_DEVICE(direct_x_proxy) \
	EXPECT_CALL(*(direct_x_proxy), CreateDevice(_, D3D_DRIVER_TYPE_WARP, _, _, _, _, _, _, _, _))


TEST(DeviceFactoryTest, shouldCreateDevice) {
	DeviceFactoryTestSetup setup;

	EXPECT_CHECK_DEBUG_LAYER_SUPPORT(setup.direct_x_proxy).Times(AtMost(1));
	EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(setup.direct_x_proxy).WillOnce(Return(0));

	setup.direct_x_device_factory->CreateDirectXDevice();
}

TEST(DeviceFactoryTest, shouldCreateFallbackDeviceWhenHardwareAccelerationNotSupported) {
	DeviceFactoryTestSetup setup;

	EXPECT_CHECK_DEBUG_LAYER_SUPPORT(setup.direct_x_proxy).Times(AtMost(1));
	EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(setup.direct_x_proxy).WillOnce(Return(-1));
	EXPECT_CREATE_FALLBACK_DEVICE(setup.direct_x_proxy).WillOnce(Return(0));

	setup.direct_x_device_factory->CreateDirectXDevice();
}
