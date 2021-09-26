#pragma once

using byte = unsigned char;

class ImageBuffer {
public:
    int width;
    int height;
    byte* buffer;
    ImageBuffer() {}
};