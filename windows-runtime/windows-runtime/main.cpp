#include "pch.h"

#include <memory>

#include "App/AppAdapter.h"
#include "Graphics/DirectXProxyImpl.h"
#include "Graphics/DirectXDeviceFactoryImpl.h"

using namespace std;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    shared_ptr<DirectXProxy> direct_x_proxy = make_shared<DirectXProxyImpl>();
    shared_ptr<DirectXDeviceFactory> direct_x_device_factory = make_shared<DirectXDeviceFactoryImpl>(direct_x_proxy);
    shared_ptr<App> app = make_shared<App>(direct_x_device_factory);
    CoreApplication::Run(make<AppAdapter>(app));
}
