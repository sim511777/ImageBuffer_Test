#pragma once

namespace hims {
using byte = unsigned char;

enum class EPixelType {
    Bpp8Gray,
    Bpp24Bgr,
    Bpp32Bgr,
    Bpp16Gray,
    Bpp32GrayFloat,
    Unknown,
};
}