#include "pch.h"

#include <memory>
#include "../../windows-runtime/Graphics/ViewImpl.h"

using ::testing::Return;

class GraphicsDeviceContainerMock : public GraphicsDeviceContainer {
public:
	MOCK_METHOD(void, Create, (), (override));
	MOCK_METHOD(void, Trim, (), (override));

	MOCK_METHOD(ID3D11Device3*, GetDevice, (), (override));
	MOCK_METHOD(IDXGIDevice3*, GetGIDevice, (), (override));
	MOCK_METHOD(ID3D11DeviceContext3*, GetContext, (), (override));
};

class DoubleBufferMock : public DoubleBuffer {
public:
	MOCK_METHOD(void, SetWindow, (winrt::Windows::UI::Core::CoreWindow const* window), (override));
	MOCK_METHOD(bool, Create, (), (override));
	MOCK_METHOD(void, StartFrame, (), (override));
	MOCK_METHOD(bool, FinishFrame, (), (override));
	MOCK_METHOD(void, Destroy, (), (override));
};

class PainterMock : public Painter {
public:
	MOCK_METHOD(winrt::Windows::Foundation::IAsyncAction, CreateResources, (), (override));
	MOCK_METHOD(void, Paint, (), (override));
};

struct ViewTestSetup {
	std::shared_ptr<View> view;
	std::shared_ptr<GraphicsDeviceContainerMock> graphics_device_container_mock;
	std::shared_ptr<DoubleBufferMock> double_buffer_mock;
	std::shared_ptr<PainterMock> painter_mock;
};

ViewTestSetup createViewTestSetup() {
	ViewTestSetup setup;

	setup.graphics_device_container_mock = std::make_shared<GraphicsDeviceContainerMock>();
	setup.double_buffer_mock = std::make_shared<DoubleBufferMock>();
	setup.painter_mock = std::make_shared<PainterMock>();

	setup.view = std::make_shared<ViewImpl>(
		*setup.graphics_device_container_mock,
		*setup.double_buffer_mock,
		std::vector<std::shared_ptr<Painter>>{setup.painter_mock}
	);

	return setup;
}

void expectResetDevice(ViewTestSetup setup) {
	EXPECT_CALL(*setup.double_buffer_mock, Create()).WillRepeatedly(Return(true));
	EXPECT_CALL(*setup.double_buffer_mock, Destroy());
	EXPECT_CALL(*setup.graphics_device_container_mock, Create);
	EXPECT_CALL(*setup.painter_mock, CreateResources).WillOnce([]() -> winrt::Windows::Foundation::IAsyncAction {
		co_return;
	});
}

TEST(ViewTest, ShouldCreateDeviceOnInitialization) {
	ViewTestSetup setup = createViewTestSetup();
	EXPECT_CALL(*setup.graphics_device_container_mock, Create);

	setup.view->OnInitialize();
}

TEST(ViewTest, ShouldInitializeDoubleBufferOnSetWindow) {
	using CoreWindow = winrt::Windows::UI::Core::CoreWindow;
	
	ViewTestSetup setup = createViewTestSetup();
	CoreWindow const* window_mock = reinterpret_cast<CoreWindow const*>(123);
	EXPECT_CALL(*setup.double_buffer_mock, SetWindow(window_mock));
	EXPECT_CALL(*setup.double_buffer_mock, Create());

	setup.view->OnSetWindow(window_mock);
}

TEST(ViewTest, ShouldCreatePainterResourcesOnLoad) {
	ViewTestSetup setup = createViewTestSetup();
	EXPECT_CALL(*setup.painter_mock, CreateResources).WillOnce([]() -> winrt::Windows::Foundation::IAsyncAction {
		co_return;
	});

	setup.view->OnLoad();
}

TEST(ViewTest, ShouldTrimDeviceOnSuspending) {
	ViewTestSetup setup = createViewTestSetup();
	EXPECT_CALL(*setup.graphics_device_container_mock, Trim);

	setup.view->OnSuspending();
}

TEST(ViewTest, ShouldRecreateDoubleBufferOnResize) {
	ViewTestSetup setup = createViewTestSetup();
	EXPECT_CALL(*setup.double_buffer_mock, Create())
		.WillOnce(Return(true));

	setup.view->OnResize();
}

TEST(ViewTest, ShouldResetDeviceWhenDoubleBufferRecreateFails) {
	ViewTestSetup setup = createViewTestSetup();
	expectResetDevice(setup);
	EXPECT_CALL(*setup.double_buffer_mock, Create())
		.WillOnce(Return(false))
		.WillOnce(Return(true));

	setup.view->OnResize();
}

TEST(ViewTest, ShouldPaintFrame) {
	ViewTestSetup setup = createViewTestSetup();
	EXPECT_CALL(*setup.double_buffer_mock, StartFrame());
	EXPECT_CALL(*setup.painter_mock, Paint);
	EXPECT_CALL(*setup.double_buffer_mock, FinishFrame())
		.WillOnce(Return(true));

	setup.view->Paint();
}

TEST(ViewTest, ShouldResetDeviceWhenFrameFails) {
	ViewTestSetup setup = createViewTestSetup();
	expectResetDevice(setup);
	EXPECT_CALL(*setup.double_buffer_mock, StartFrame());
	EXPECT_CALL(*setup.painter_mock, Paint);
	EXPECT_CALL(*setup.double_buffer_mock, FinishFrame())
		.WillOnce(Return(false));

	setup.view->Paint();
}
