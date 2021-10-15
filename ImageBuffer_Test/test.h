#pragma once

#include "ImageBuffer.h"
#include <stdio.h>

void TestImageBuffer() {
    ImageBuffer img(64, 64, 64);
    printf("width:%lld height:%lld buffer:%p", img.Width(), img.Height(), img.Buffer());
}