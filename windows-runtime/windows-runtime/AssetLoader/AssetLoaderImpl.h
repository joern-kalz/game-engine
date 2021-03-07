#pragma once

#include "AssetLoader.h"

class AssetLoaderImpl : public AssetLoader {
public:
    AssetLoaderImpl();

    virtual IAsyncAction LoadBuffer(winrt::hstring filename, IBuffer* buffer) override;
    virtual IAsyncAction LoadImage(winrt::hstring filename, Image* image) override;

private:
    void CreateWicFactory();
    void LoadImageFromBuffer(IBuffer* buffer, Image* image);

    winrt::Windows::Storage::StorageFolder installed_location_;
    winrt::com_ptr<IWICImagingFactory2> wic_factory_;
};