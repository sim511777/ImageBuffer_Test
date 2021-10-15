#pragma once

using byte = unsigned char;

class ImageBuffer {
private:
    int width;
    int height;
    byte* buffer;
public:
    int Width() {
        return width;
    }
    int Height() {
        return height;
    }
    byte* Buffer() {
        return buffer;
    }
    ImageBuffer(int width, int height) {
        this->width = width;
        this->height = height;
        this->buffer = new byte[width * height];
    }
    ~ImageBuffer() {
        delete[] buffer;
    }
};