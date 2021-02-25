#include "pch.h"

#include <memory>

#include "App/AppAdapter.h"
#include "Graphics/GraphicsFacade.h"
#include "Graphics/DirectXFactoryImpl.h"

using namespace std;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    shared_ptr<DirectXFactoryImpl> direct_x_factory = make_shared<DirectXFactoryImpl>();
    shared_ptr<GraphicsFacade> graphicsFacade = make_shared<GraphicsFacade>(direct_x_factory);
    shared_ptr<App> app = make_shared<App>(graphicsFacade);
    CoreApplication::Run(make<AppAdapter>(app));
}
