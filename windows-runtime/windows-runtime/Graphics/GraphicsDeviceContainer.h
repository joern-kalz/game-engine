#pragma once

#include "GraphicsDeviceProvider.h"

class GraphicsDeviceContainer : public GraphicsDeviceProvider {
public:
    virtual void Create() = 0;
    virtual void Trim() = 0;
};

