#include "pch.h"

#include <memory>

#include "App/AppAdapter.h"
#include "App/AppImpl.h"
#include "AssetLoader/AssetLoaderImpl.h"
#include "Graphics/DoubleBufferImpl.h"
#include "Graphics/GraphicsDeviceContainerImpl.h"
#include "Graphics/GraphicsResourceFactoryImpl.h"
#include "Graphics/TexturedRectanglePainter.h"
#include "Graphics/ViewImpl.h"

using namespace std;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    AssetLoaderImpl asset_loader;

    GraphicsDeviceContainerImpl graphics_device_container;
    DoubleBufferImpl double_buffer(graphics_device_container);
    GraphicsResourceFactoryImpl graphics_resource_factory(graphics_device_container, asset_loader);

    std::vector<std::shared_ptr<Painter>> painters{
        std::make_shared< TexturedRectanglePainter>(graphics_device_container, graphics_resource_factory),
    };

    ViewImpl view(graphics_device_container, double_buffer, painters);
    AppImpl app(view);

    winrt::Windows::ApplicationModel::Core::CoreApplication::Run(winrt::make<AppAdapter>(app));
}
