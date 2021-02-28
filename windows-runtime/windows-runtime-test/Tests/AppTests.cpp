#include "pch.h"

#include "ID3D11Device3Mock.h"
#include "../../windows-runtime/App/App.h"
#include "../../windows-runtime/Graphics/DirectXDeviceFactory.h"

using ::testing::_;
using ::testing::AtMost;
using ::testing::Return;

class DirectXDeviceFactoryStub : public DirectXDeviceFactory {
public:
	DirectXDeviceFactoryStub(std::shared_ptr<DirectXDevice> device) : device_(device) {}
	virtual std::shared_ptr<DirectXDevice> CreateDirectXDevice() { return device_; }
private:
	std::shared_ptr<DirectXDevice> device_;
};

struct AppTestSetup {
	ID3D11Device3Mock id3d11_device_3_mock;
	std::shared_ptr<winrt::com_ptr<ID3D11Device3>> id3d11_device_3 = std::make_shared<winrt::com_ptr<ID3D11Device3>>();
	std::shared_ptr<DirectXDevice> direct_x_device = std::make_shared<DirectXDevice>(id3d11_device_3, std::shared_ptr<winrt::com_ptr<ID3D11DeviceContext3>>(nullptr), D3D_FEATURE_LEVEL());
	std::shared_ptr<DirectXDeviceFactory> direct_x_device_factory = std::make_shared<DirectXDeviceFactoryStub>(direct_x_device);
	std::shared_ptr<App> app = std::make_shared<App>(direct_x_device_factory);
	AppTestSetup() {
		*id3d11_device_3->put() = &id3d11_device_3_mock;
	}
};

TEST(AppTest, ShouldCreateSamplerState) {
	AppTestSetup setup;
	EXPECT_CALL(setup.id3d11_device_3_mock, CreateSamplerState(_, _));
	setup.app->OnInitialize();
	setup.app->OnLoad();
}