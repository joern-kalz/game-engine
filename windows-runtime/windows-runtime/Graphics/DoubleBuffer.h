#pragma once

class DoubleBuffer {
public:
    virtual ~DoubleBuffer() {}

    virtual void SetWindow(winrt::Windows::UI::Core::CoreWindow const* window) = 0;

    virtual bool Create() = 0;
    virtual void Destroy() = 0;

    virtual void StartFrame() = 0;
    virtual bool FinishFrame() = 0;
};

