#include "pch.h"

#include "AppTestSetup.h"

using ::testing::_;
using ::testing::AtMost;
using ::testing::Return;

TEST(AppInitializationTest, shouldCreateDevice) {
	AppTestSetup setup;

	EXPECT_CHECK_DEBUG_LAYER_SUPPORT(setup.direct_x_factory).Times(AtMost(1));
	EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(setup.direct_x_factory).WillOnce(Return(0));

	setup.app->OnInitialize();
}

TEST(AppInitializationTest, shouldCreateFallbackDeviceWhenHardwareAccelerationNotSupported) {
	AppTestSetup setup;

	EXPECT_CHECK_DEBUG_LAYER_SUPPORT(setup.direct_x_factory).Times(AtMost(1));
	EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(setup.direct_x_factory).WillOnce(Return(-1));
	EXPECT_CREATE_FALLBACK_DEVICE(setup.direct_x_factory).WillOnce(Return(0));

	setup.app->OnInitialize();
}
