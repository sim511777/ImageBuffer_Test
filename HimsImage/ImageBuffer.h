#pragma once

#include <memory>
#include <string>
#include "ImageDefs.h"

namespace hims {
class ImageBuffer {
private:
    size_t width;
    size_t height;
    size_t stride;
    EPixelType pixelType;
    std::shared_ptr<byte> sharedBuffer;
    byte* buffer;

    void InitInfo(size_t width, size_t height, size_t stride, EPixelType pixelType, byte* buffer);

public:
    // �ʺ�
    size_t Width();
    // ����
    size_t Height();
    // y step byte count
    size_t Stride();
    // �ȼ�Ÿ��
    EPixelType PixelType();
    // ���� ������
    byte* Buffer();
    // pixel byte count
    int GetBytesPerPixel();

    // ������ - �ܺι���
    ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType, byte* externalBuffer);
    // ������ - �����Ҵ�
    ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType);
    // ������ - �̹��� ���� ���
    ImageBuffer(std::wstring imageFilePath);
};
}