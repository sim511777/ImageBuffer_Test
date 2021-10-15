#pragma once

#include <memory>
#include <string>
#include "ImageFileUtil.h"

using byte = unsigned char;

class ImageBuffer {
private:
    size_t width;
    size_t height;
    size_t stride;
    std::shared_ptr<byte> sharedBuffer;
    byte* buffer;

    void InitInfo(size_t width, size_t height, size_t stride, byte* buffer) {
        this->width = width;
        this->height = height;
        this->stride = stride;
        this->buffer = buffer;
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

    byte* Buffer() {
        return buffer;
    }

    // ������ - �ܺι���
    ImageBuffer(size_t width, size_t height, size_t stride, byte* externalBuffer) {
        InitInfo(width, height, stride, externalBuffer);
    }

    // ������ - �����Ҵ�
    ImageBuffer(size_t width, size_t height, size_t stride) {
        sharedBuffer = std::shared_ptr<byte>(new byte[width * stride], [](byte *p) { delete[] p; });
        InitInfo(width, height, stride, sharedBuffer.get());
    }

    // ������ - �̹��� ���� ���
    ImageBuffer(std::wstring imageFilePath) {
        size_t width, height, stride;
        ReadImageFileHeader(imageFilePath, &width, &height, &stride);
        sharedBuffer = std::shared_ptr<byte>(new byte[width * stride], [](byte *p) { delete[] p; });
        InitInfo(width, height, stride, sharedBuffer.get());
        ReadImageFileBuffer(imageFilePath, buffer);
    }
};