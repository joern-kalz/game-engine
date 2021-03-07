#pragma once

class GraphicsDeviceProvider {
public:
    virtual ~GraphicsDeviceProvider() {}
    virtual ID3D11Device3* GetDevice() = 0;
    virtual IDXGIDevice3* GetGIDevice() = 0;
    virtual ID3D11DeviceContext3* GetContext() = 0;
};

