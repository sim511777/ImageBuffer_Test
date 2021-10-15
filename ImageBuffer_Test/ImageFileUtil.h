#pragma once

#include <memory>
#include <string>
#include "ImageDefs.h"

void ReadImageFileHeader(std::wstring imageFilePath, size_t* pWidth, size_t* pHeight, size_t* pStride, EPixelType* pPixelType) {
    // todo
    *pWidth = 64;
    *pHeight = 64;
    *pStride = 64;
    *pPixelType = EPixelType::Gray8bpp;
}

void ReadImageFileBuffer(std::wstring imageFilePath, byte* buffer) {
    // todo
}
