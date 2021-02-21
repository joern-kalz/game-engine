#include "pch.h"

#include <memory>

#include "RenderApiDirectX.h"
#include "AppAdapter.h"

using namespace std;

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    shared_ptr<RenderApi> renderApi = make_shared<RenderApiDirectX>();
    shared_ptr<App> app = make_shared<App>(renderApi);
    CoreApplication::Run(make<AppAdapter>(app));
}
