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

ViewTestSetup CreateViewTestSetup() {
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

void ExpectCreateResourcesOfPainter(ViewTestSetup setup) {
	EXPECT_CALL(*setup.painter_mock, CreateResources).WillOnce([]() -> winrt::Windows::Foundation::IAsyncAction {
		co_return;
	});
}

void ExpectResetDevice(ViewTestSetup setup) {
	EXPECT_CALL(*setup.double_buffer_mock, Create()).WillRepeatedly(Return(true));
	EXPECT_CALL(*setup.double_buffer_mock, Destroy());
	EXPECT_CALL(*setup.graphics_device_container_mock, Create);
	ExpectCreateResourcesOfPainter(setup);
}

void ExpectFrameAndSucceed(ViewTestSetup setup) {
	EXPECT_CALL(*setup.double_buffer_mock, StartFrame());
	EXPECT_CALL(*setup.double_buffer_mock, FinishFrame())
		.WillOnce(Return(true));
}

void ExpectFrameAndFail(ViewTestSetup setup) {
	EXPECT_CALL(*setup.double_buffer_mock, StartFrame());
	EXPECT_CALL(*setup.double_buffer_mock, FinishFrame())
		.WillOnce(Return(false));
}

void CreatePainterResources(ViewTestSetup setup) {
	ExpectCreateResourcesOfPainter(setup);
	setup.view->OnLoad();
}

TEST(ViewTest, ShouldCreateDeviceOnInitialization) {
	ViewTestSetup setup = CreateViewTestSetup();
	EXPECT_CALL(*setup.graphics_device_container_mock, Create);

	setup.view->OnInitialize();
}

TEST(ViewTest, ShouldInitializeDoubleBufferOnSetWindow) {
	using CoreWindow = winrt::Windows::UI::Core::CoreWindow;
	
	ViewTestSetup setup = CreateViewTestSetup();
	CoreWindow const* window_mock = reinterpret_cast<CoreWindow const*>(123);
	EXPECT_CALL(*setup.double_buffer_mock, SetWindow(window_mock));
	EXPECT_CALL(*setup.double_buffer_mock, Create());

	setup.view->OnSetWindow(window_mock);
}

TEST(ViewTest, ShouldCreatePainterResourcesOnLoad) {
	ViewTestSetup setup = CreateViewTestSetup();
	ExpectCreateResourcesOfPainter(setup);

	setup.view->OnLoad();
}

TEST(ViewTest, ShouldTrimDeviceOnSuspending) {
	ViewTestSetup setup = CreateViewTestSetup();
	EXPECT_CALL(*setup.graphics_device_container_mock, Trim);

	setup.view->OnSuspending();
}

TEST(ViewTest, ShouldRecreateDoubleBufferOnResize) {
	ViewTestSetup setup = CreateViewTestSetup();
	EXPECT_CALL(*setup.double_buffer_mock, Create())
		.WillOnce(Return(true));

	setup.view->OnResize();
}

TEST(ViewTest, ShouldResetDeviceWhenDoubleBufferRecreateFails) {
	ViewTestSetup setup = CreateViewTestSetup();
	ExpectResetDevice(setup);
	EXPECT_CALL(*setup.double_buffer_mock, Create())
		.WillOnce(Return(false))
		.WillOnce(Return(true));

	setup.view->OnResize();
}

TEST(ViewTest, ShouldPaintFrame) {
	ViewTestSetup setup = CreateViewTestSetup();
	ExpectFrameAndSucceed(setup);

	setup.view->Paint();
}

TEST(ViewTest, ShouldNotInvokePainterIfPainterResourcesNotCreated) {
	ViewTestSetup setup = CreateViewTestSetup();
	ExpectFrameAndSucceed(setup);
	EXPECT_CALL(*setup.painter_mock, Paint).Times(0);

	setup.view->Paint();
}

TEST(ViewTest, ShouldInvokePainterIfPainterResourcesCreated) {
	ViewTestSetup setup = CreateViewTestSetup();
	ExpectFrameAndSucceed(setup);
	EXPECT_CALL(*setup.painter_mock, Paint).Times(1);
	CreatePainterResources(setup);

	setup.view->Paint();
}

TEST(ViewTest, ShouldResetDeviceWhenFrameFails) {
	ViewTestSetup setup = CreateViewTestSetup();
	ExpectFrameAndFail(setup);
	ExpectResetDevice(setup);

	setup.view->Paint();
}
