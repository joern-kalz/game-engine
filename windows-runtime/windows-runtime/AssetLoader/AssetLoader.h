#pragma once

class AssetLoader {
public:
    using IAsyncAction = winrt::Windows::Foundation::IAsyncAction;
    using IBuffer = winrt::Windows::Storage::Streams::IBuffer;
    struct Image { int width; int height; std::unique_ptr<byte[]> data; };

    virtual ~AssetLoader() {}
    virtual IAsyncAction LoadBuffer(winrt::hstring filename, IBuffer* buffer) = 0;
    virtual IAsyncAction LoadImage(winrt::hstring filename, Image* image) = 0;
};