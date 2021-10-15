#pragma once

#include <memory>
#include <string>
#include "ImageFileUtil.h"

using byte = unsigned char;

class ImageBuffer {
private:
    int width;
    int height;
    int stride;
    std::shared_ptr<byte> sharedBuffer;
    byte* buffer;

    void InitInfo(int width, int height, int stride, byte* buffer) {
        this->width = width;
        this->height = height;
        this->stride = stride;
        this->buffer = buffer;
    }

    void Init(int width, int height, int stride) {
        sharedBuffer = std::shared_ptr<byte>(new byte[width * stride], [](byte *p) { delete[] p; });
        InitInfo(width, height, stride, sharedBuffer.get());
    }

public:
    int Width() {
        return width;
    }

    int Height() {
        return height;
    }

    int Stride() {
        return stride;
    }

    byte* Buffer() {
        return buffer;
    }

    // ������ - �ܺι���
    ImageBuffer(int width, int height, int stride, byte* externalBuffer) {
        InitInfo(width, height, stride, externalBuffer);
    }

    // ������ - �����Ҵ�
    ImageBuffer(int width, int height, int stride) {
        Init(width, height, stride);
    }

    // ������ - �̹��� ���� ���
    ImageBuffer(std::wstring imageFilePath) {
        int width, height, stride;
        ReadImageFileHeader(imageFilePath, &width, &height, &stride);
        Init(width, height, stride);
        ReadImageFileBuffer(imageFilePath, buffer);
    }
};