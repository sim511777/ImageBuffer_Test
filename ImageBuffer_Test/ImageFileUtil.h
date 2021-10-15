#pragma once

#include <memory>
#include <string>

using byte = unsigned char;

void ReadImageFileHeader(std::wstring imageFilePath, int* pWidth, int* pHeight, int* pStride) {
    // todo
    *pWidth = 64;
    *pHeight = 64;
    *pStride = 64;
}

void ReadImageFileBuffer(std::wstring imageFilePath, byte* buffer) {
    // todo
}
