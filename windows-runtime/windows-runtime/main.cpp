#include "pch.h"

#include <memory>

#include "App/AppAdapter.h"
#include "Graphics/GraphicsFacade.h"
#include "Graphics/GraphicsLibraryImpl.h"

using namespace std;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    shared_ptr<GraphicsLibraryImpl> graphicsLibrary = make_shared<GraphicsLibraryImpl>();
    shared_ptr<GraphicsFacade> graphicsFacade = make_shared<GraphicsFacade>(graphicsLibrary);
    shared_ptr<App> app = make_shared<App>(graphicsFacade);
    CoreApplication::Run(make<AppAdapter>(app));
}
