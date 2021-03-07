#include "pch.h"

#include <memory>
#include "../../windows-runtime/App/AppImpl.h"

class ViewMock : public View {
public:
	MOCK_METHOD(void, OnInitialize, (), (override));
	MOCK_METHOD(void, OnSetWindow, (winrt::Windows::UI::Core::CoreWindow const* window), (override));
	MOCK_METHOD(void, OnLoad, (), (override));
	MOCK_METHOD(void, OnSuspending, (), (override));
	MOCK_METHOD(void, OnResize, (), (override));
	MOCK_METHOD(void, Paint, (), (override));
};

struct AppTestSetup {
	std::shared_ptr<App> app;
	std::shared_ptr<ViewMock> view_mock;
};

AppTestSetup createAppTestSetup() {
	AppTestSetup setup;
	setup.view_mock = std::make_shared<ViewMock>();
	setup.app = std::make_shared<AppImpl>(*setup.view_mock);
	return setup;
}

TEST(AppTest, ShouldInitializeView) {
	AppTestSetup setup = createAppTestSetup();
	EXPECT_CALL(*setup.view_mock, OnInitialize);

	setup.app->OnInitialize();
}

TEST(AppTest, ShouldSetViewWindow) {
	using CoreWindow = winrt::Windows::UI::Core::CoreWindow;

	AppTestSetup setup = createAppTestSetup();
	CoreWindow const* window_mock = reinterpret_cast<CoreWindow const*>(123);
	EXPECT_CALL(*setup.view_mock, OnSetWindow(window_mock));

	setup.app->OnSetWindow(window_mock);
}

TEST(AppTest, ShouldLoadView) {
	AppTestSetup setup = createAppTestSetup();
	EXPECT_CALL(*setup.view_mock, OnLoad());

	setup.app->OnLoad();
}

TEST(AppTest, ShouldRunView) {
	AppTestSetup setup = createAppTestSetup();
	EXPECT_CALL(*setup.view_mock, Paint());

	setup.app->OnRun();
}

TEST(AppTest, ShouldSuspendView) {
	AppTestSetup setup = createAppTestSetup();
	EXPECT_CALL(*setup.view_mock, OnSuspending());

	setup.app->OnSuspending();
}

TEST(AppTest, ShouldResizeView) {
	AppTestSetup setup = createAppTestSetup();
	EXPECT_CALL(*setup.view_mock, OnResize());

	setup.app->OnResize();
}
