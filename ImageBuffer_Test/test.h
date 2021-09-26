#pragma once

#include "ImageBuffer.h"

void TestImageBuffer() {
    ImageBuffer img;
    wchar_t str[1024];
    wsprintf(str, L"width:%d height:%d buffer:%p", img.width, img.height, img.buffer);
    MessageBox(NULL, str, NULL, NULL);
}