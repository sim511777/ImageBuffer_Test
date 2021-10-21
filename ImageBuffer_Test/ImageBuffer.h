#pragma once

#include <memory>
#include <string>
#include "ImageFileUtil.h"
#include "ImageDefs.h"

class ImageBuffer {
private:
    size_t width;
    size_t height;
    size_t stride;
    EPixelType pixelType;
    std::shared_ptr<byte> sharedBuffer;
    byte* buffer;

    void InitInfo(size_t width, size_t height, size_t stride, EPixelType pixelType, byte* buffer) {
        this->width = width;
        this->height = height;
        this->stride = stride;
        this->buffer = buffer;
        this->pixelType = pixelType;
    }

public:
    size_t Width() {
        return width;
    }

    size_t Height() {
        return height;
    }

    size_t Stride() {
        return stride;
    }

    EPixelType PixelType() {
        return pixelType;
    }

    byte* Buffer() {
        return buffer;
    }

    int GetBytesPerPixel() {
        switch (pixelType) {
        case EPixelType::Bpp8Gray:          return 1;   break;
        case EPixelType::Bpp24Bgr:          return 3;   break;
        case EPixelType::Bpp32Bgr:          return 4;   break;
        case EPixelType::Bpp16Gray:         return 2;   break;
        case EPixelType::Bpp32GrayFloat:    return 4;   break;
        case EPixelType::Unknown:           return 0;   break;
        default:                            return 0;   break;
        }
    }

    // ������ - �ܺι���
    ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType, byte* externalBuffer) {
        InitInfo(width, height, stride, pixelType, externalBuffer);
    }

    // ������ - �����Ҵ�
    ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType) {
        sharedBuffer = std::shared_ptr<byte>(new byte[width * stride], [](byte *p) { delete[] p; });
        InitInfo(width, height, stride, pixelType, sharedBuffer.get());
    }

    // ������ - �̹��� ���� ���
    ImageBuffer(std::wstring imageFilePath) {
        bool r = false;
        size_t width, height, stride;
        EPixelType pixelType;
        r = ReadImageFileHeader(imageFilePath, &width, &height, &stride, &pixelType);
        if (!r)
            return;
        sharedBuffer = std::shared_ptr<byte>(new byte[width * stride], [](byte *p) { delete[] p; });
        InitInfo(width, height, stride, pixelType, sharedBuffer.get());
        ReadImageFileBuffer(imageFilePath, buffer, width, height, stride);
        if (!r)
            return;
    }
};