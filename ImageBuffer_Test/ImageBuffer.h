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

    // 생성자 - 외부버퍼
    ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType, byte* externalBuffer) {
        InitInfo(width, height, stride, pixelType, externalBuffer);
    }

    // 생성자 - 내부할당
    ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType) {
        sharedBuffer = std::shared_ptr<byte>(new byte[width * stride], [](byte *p) { delete[] p; });
        InitInfo(width, height, stride, pixelType, sharedBuffer.get());
    }

    // 생성자 - 이미지 파일 경로
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