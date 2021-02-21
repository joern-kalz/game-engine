#include "pch.h"

#include "gmock/gmock.h"

#include "../windows-runtime/App.h"

class RenderApiMock : public RenderApi {
public:
	MOCK_METHOD(void, Initialize, (), (override));
};

TEST(AppTest, shouldInitializeRenderApi) {
	auto renderApiMock = make_shared<RenderApiMock>();
	App app(renderApiMock);
	EXPECT_CALL(*renderApiMock, Initialize());

	app.OnInitialize();
}