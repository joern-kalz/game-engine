#include "pch.h"

#include "AppTestSetup.h"

using ::testing::_;
using ::testing::AtMost;
using ::testing::Return;

struct TestSetup {
	shared_ptr<GraphicsLibraryMock> graphicsLibrary = make_shared<GraphicsLibraryMock>();
	shared_ptr<GraphicsFacade> graphicsFacade = make_shared<GraphicsFacade>(graphicsLibrary);
	shared_ptr<App> app = make_shared<App>(graphicsFacade);
};

TEST(AppInitializationTest, shouldCreateDevice) {
	AppTestSetup setup;

	EXPECT_CHECK_DEBUG_LAYER_SUPPORT(setup.graphicsLibrary).Times(AtMost(1));
	EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(setup.graphicsLibrary).WillOnce(Return(0));

	setup.app->OnInitialize();
}

TEST(AppInitializationTest, shouldCreateFallbackDeviceWhenHardwareAccelerationNotSupported) {
	AppTestSetup setup;

	EXPECT_CHECK_DEBUG_LAYER_SUPPORT(setup.graphicsLibrary).Times(AtMost(1));
	EXPECT_CREATE_HARDWARE_ACCELERATED_DEVICE(setup.graphicsLibrary).WillOnce(Return(-1));
	EXPECT_CREATE_FALLBACK_DEVICE(setup.graphicsLibrary).WillOnce(Return(0));

	setup.app->OnInitialize();
}
