#pragma once

#include <string>
#include "ImageDefs.h"

namespace hims {
bool ReadImageFileHeader(std::wstring imageFilePath, size_t* pWidth, size_t* pHeight, size_t* pStride, EPixelType* pPixelType);
bool ReadImageFileBuffer(std::wstring imageFilePath, byte* buffer, size_t width, size_t height, size_t stride);
}
