#pragma once

#include "ImageBuffer.h"
#include <stdio.h>

void TestImageBuffer() {
    //ImageBuffer img(64, 64, 64, EPixelType::Gray8bpp);
    ImageBuffer img(L"c:\\test\\8K Aqua.png");
    printf("width:%lld height:%lld buffer:%p", img.Width(), img.Height(), img.Buffer());
}