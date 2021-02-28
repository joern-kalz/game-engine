#pragma once

#include <memory>

#include "DirectXDevice.h"

class DirectXDeviceFactory {
public:
    virtual std::shared_ptr<DirectXDevice> CreateDirectXDevice() = 0;
};

