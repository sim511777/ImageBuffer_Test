#pragma once

#include <memory>
#include <string>
#include <wincodec.h>
#include "ImageDefs.h"

#pragma comment(lib, "windowscodecs.lib")

template <typename T>
inline void SafeRelease(T *&p) {
    if (NULL != p) {
        p->Release();
        p = NULL;
    }
}

bool ReadImageFileHeader(std::wstring imageFilePath, size_t* pWidth, size_t* pHeight, size_t* pStride, EPixelType* pPixelType) {
    bool result = false;
    
    HRESULT hr;

    IWICImagingFactory *pFactory = NULL;
    IWICBitmapDecoder *pDecoder = NULL;
    IWICBitmapFrameDecode *pFrame = NULL;
    IWICComponentInfo *pCompInfo = NULL;
    IWICPixelFormatInfo *pPixelInfo = NULL;

    do {
        hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (!SUCCEEDED(hr))
            break;

        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&pFactory)
        );

        if (!SUCCEEDED(hr))
            break;

        hr = pFactory->CreateDecoderFromFilename(
            imageFilePath.c_str(),                      // Image to be decoded
            NULL,                            // Do not prefer a particular vendor
            GENERIC_READ,                    // Desired read access to the file
            WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
            &pDecoder                        // Pointer to the decoder
        );

        if (!SUCCEEDED(hr))
            break;

        hr = pDecoder->GetFrame(0, &pFrame);

        if (!SUCCEEDED(hr))
            break;

        UINT width;
        UINT height;
        WICPixelFormatGUID pixelFormat;
        pFrame->GetSize(&width, &height);
        pFrame->GetPixelFormat(&pixelFormat);

        hr = pFactory->CreateComponentInfo(pixelFormat, &pCompInfo);
        if (!SUCCEEDED(hr))
            break;

        pCompInfo->QueryInterface(__uuidof(IWICPixelFormatInfo), reinterpret_cast<void**>(&pPixelInfo));
        if (!SUCCEEDED(hr))
            break;

        UINT bpp;
        UINT ch;
        pPixelInfo->GetBitsPerPixel(&bpp);
        pPixelInfo->GetChannelCount(&ch);

        *pWidth = width;
        *pHeight = height;
        size_t bytesPerLine = (width * bpp + 7) / 8;
        //*pStride = (bytesPerLine + 3) / 4 * 4;
        *pStride = bytesPerLine;
        if (pixelFormat == GUID_WICPixelFormat8bppIndexed || pixelFormat == GUID_WICPixelFormat8bppGray)
            *pPixelType = EPixelType::Bpp8Gray;
        else if (pixelFormat == GUID_WICPixelFormat24bppBGR)
            *pPixelType = EPixelType::Bpp24Bgr;
        else if (pixelFormat == GUID_WICPixelFormat32bppBGR || pixelFormat == GUID_WICPixelFormat32bppBGRA || pixelFormat == GUID_WICPixelFormat32bppPBGRA)
            *pPixelType = EPixelType::Bpp32Bgr;
        else if (pixelFormat == GUID_WICPixelFormat16bppGray)
            *pPixelType = EPixelType::Bpp16Gray;
        else if (pixelFormat == GUID_WICPixelFormat32bppGrayFloat)
            *pPixelType = EPixelType::Bpp32GrayFloat;
        else
            *pPixelType = EPixelType::Unknown;

        result = true;
    } while (false);

    SafeRelease(pPixelInfo);
    SafeRelease(pCompInfo);
    SafeRelease(pFrame);
    SafeRelease(pDecoder);
    SafeRelease(pFactory);

    CoUninitialize();
    
    return result;
}

bool ReadImageFileBuffer(std::wstring imageFilePath, byte* buffer, size_t width, size_t height, size_t stride) {
    bool result = false;

    HRESULT hr;

    IWICImagingFactory *pFactory = NULL;
    IWICBitmapDecoder *pDecoder = NULL;
    IWICBitmapFrameDecode *pFrame = NULL;

    do {
        hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED | COINIT_DISABLE_OLE1DDE);
        if (!SUCCEEDED(hr))
            break;

        hr = CoCreateInstance(
            CLSID_WICImagingFactory,
            NULL,
            CLSCTX_INPROC_SERVER,
            IID_PPV_ARGS(&pFactory)
        );

        if (!SUCCEEDED(hr))
            break;

        hr = pFactory->CreateDecoderFromFilename(
            imageFilePath.c_str(),                      // Image to be decoded
            NULL,                            // Do not prefer a particular vendor
            GENERIC_READ,                    // Desired read access to the file
            WICDecodeMetadataCacheOnDemand,  // Cache metadata when needed
            &pDecoder                        // Pointer to the decoder
        );

        if (!SUCCEEDED(hr))
            break;

        hr = pDecoder->GetFrame(0, &pFrame);

        if (!SUCCEEDED(hr))
            break;


        WICRect rect{0, 0, width, height};
        pFrame->CopyPixels(&rect, stride, stride * height, buffer);

        result = true;
    } while (false);

    SafeRelease(pFrame);
    SafeRelease(pDecoder);
    SafeRelease(pFactory);

    CoUninitialize();

    return result;
}
