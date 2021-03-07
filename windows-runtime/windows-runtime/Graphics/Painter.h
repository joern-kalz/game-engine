#pragma once

class Painter {
public:
    virtual ~Painter() {}
    virtual winrt::Windows::Foundation::IAsyncAction CreateResources() = 0;
    virtual void Paint() = 0;
};

