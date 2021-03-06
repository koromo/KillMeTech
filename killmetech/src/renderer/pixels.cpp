#include "pixels.h"
#include <cassert>

namespace killme
{
    size_t numBitsOfPixelFormat(PixelFormat pf)
    {
        switch (pf)
        {
        case PixelFormat::r8g8b8a8_unorm:
            return 32;

        case PixelFormat::d16_unorm:
            return 16;

        default:
            assert(false && "Invalid PixelFormat.");
            return 0; // For warnnings
        }
    }
}