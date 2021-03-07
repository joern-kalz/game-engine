#include "pch.h"
#include "AssetLoaderImpl.h"

using namespace winrt::Windows::Storage;

AssetLoaderImpl::AssetLoaderImpl() :
    installed_location_(winrt::Windows::ApplicationModel::Package::Current().InstalledLocation())
{
}

AssetLoader::IAsyncAction AssetLoaderImpl::LoadBuffer(winrt::hstring filename, IBuffer* buffer)
{
    StorageFile file{ co_await installed_location_.GetFileAsync(filename) };
    *buffer = co_await FileIO::ReadBufferAsync(file);
}

AssetLoader::IAsyncAction AssetLoaderImpl::LoadImage(winrt::hstring filename, Image* image)
{
    if (wic_factory_.get() == nullptr) {
        CreateWicFactory();
    }

    IBuffer buffer;
    co_await LoadBuffer(filename, &buffer);

    LoadImageFromBuffer(&buffer, image);
}

void AssetLoaderImpl::CreateWicFactory() {
    winrt::check_hresult(
        CoCreateInstance(
            CLSID_WICImagingFactory,
            nullptr,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&wic_factory_)
        )
    );
}

void AssetLoaderImpl::LoadImageFromBuffer(IBuffer* buffer, Image* image) {
    winrt::com_ptr<IWICStream> stream;
    winrt::check_hresult(
        wic_factory_->CreateStream(stream.put())
    );

    winrt::check_hresult(
        stream->InitializeFromMemory(
            const_cast<WICInProcPointer>(buffer->data()),
            buffer->Length()
        )
    );

    winrt::com_ptr<IWICBitmapDecoder> bitmap_decoder;
    winrt::check_hresult(
        wic_factory_->CreateDecoderFromStream(
            stream.get(),
            nullptr,
            WICDecodeMetadataCacheOnDemand,
            bitmap_decoder.put()
        )
    );

    winrt::com_ptr<IWICBitmapFrameDecode> bitmap_frame;
    winrt::check_hresult(
        bitmap_decoder->GetFrame(0, bitmap_frame.put())
    );

    winrt::com_ptr<IWICFormatConverter> format_converter;
    winrt::check_hresult(
        wic_factory_->CreateFormatConverter(format_converter.put())
    );

    winrt::check_hresult(
        format_converter->Initialize(
            bitmap_frame.get(),
            GUID_WICPixelFormat32bppPBGRA,
            WICBitmapDitherTypeNone,
            nullptr,
            0.0,
            WICBitmapPaletteTypeCustom
        )
    );

    uint32_t width;
    uint32_t height;
    winrt::check_hresult(
        bitmap_frame->GetSize(&width, &height)
    );

    image->width = width;
    image->height = height;
    image->data = std::make_unique<byte[]>(width * height * 4);

    winrt::check_hresult(
        format_converter->CopyPixels(
            nullptr,
            width * 4,
            width * height * 4,
            image->data.get()
        )
    );
}
