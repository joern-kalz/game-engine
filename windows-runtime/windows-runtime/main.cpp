#include "pch.h"

#include "AppAdapter.h"

int __stdcall wWinMain(HINSTANCE, HINSTANCE, PWSTR, int)
{
    CoreApplication::Run(make<AppAdapter>());
}
