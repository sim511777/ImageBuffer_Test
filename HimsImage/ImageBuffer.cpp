#include "ImageBuffer.h"
#include "ImageFileUtil.h"

namespace hims {
void ImageBuffer::InitInfo(size_t width, size_t height, size_t stride, EPixelType pixelType, byte* buffer) {
    this->width = width;
    this->height = height;
    this->stride = stride;
    this->buffer = buffer;
    this->pixelType = pixelType;
}

size_t ImageBuffer::Width() {
    return width;
}

size_t ImageBuffer::Height() {
    return height;
}

size_t ImageBuffer::Stride() {
    return stride;
}

EPixelType ImageBuffer::PixelType() {
    return pixelType;
}

byte* ImageBuffer::Buffer() {
    return buffer;
}

int ImageBuffer::GetBytesPerPixel() {
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

// 생성자 - 외부버퍼
ImageBuffer::ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType, byte* externalBuffer) {
    InitInfo(width, height, stride, pixelType, externalBuffer);
}

// 생성자 - 내부할당
ImageBuffer::ImageBuffer(size_t width, size_t height, size_t stride, EPixelType pixelType) {
    sharedBuffer = std::shared_ptr<byte>(new byte[width * stride], [](byte *p) { delete[] p; });
    InitInfo(width, height, stride, pixelType, sharedBuffer.get());
}

// 생성자 - 이미지 파일 경로
ImageBuffer::ImageBuffer(std::wstring imageFilePath) {
    bool r = false;
    size_t width, height, stride;
    EPixelType pixelType;
    r = ReadImageFileHeader(imageFilePath, &width, &height, &stride, &pixelType);
    if (!r)
        return;
    sharedBuffer = std::shared_ptr<byte>(new byte[width * stride], [](byte *p) { delete[] p; });
    InitInfo(width, height, stride, pixelType, sharedBuffer.get());
    r = ReadImageFileBuffer(imageFilePath, buffer, width, height, stride);
    if (!r)
        return;
}
}