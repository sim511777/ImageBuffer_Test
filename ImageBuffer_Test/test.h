#pragma once

#include "ImageBuffer.h"
#include <stdio.h>

void TestImageBuffer() {
    ImageBuffer img(64, 64);
    printf("width:%d height:%d buffer:%p", img.Width(), img.Height(), img.Buffer());
}