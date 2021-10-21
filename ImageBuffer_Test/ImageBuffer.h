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
    // 너비
    size_t Width();
    // 높이
    size_t Height();
    // y step byte count
    size_t Stride();
    // 픽셀타입
    EPixelType PixelType();
    // 버퍼 포인터
    byte* Buffer();
    // pixel byte count
    int GetBytesPerPixel();

    // 생성자 - 외부버퍼
    ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType, byte* externalBuffer);
    // 생성자 - 내부할당
    ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType);
    // 생성자 - 이미지 파일 경로
    ImageBuffer(std::wstring imageFilePath);
};
}