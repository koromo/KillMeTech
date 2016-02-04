#ifndef _KILLME_D3DSUPPORT_H_
#define _KILLME_D3DSUPPORT_H_

#include "../core/exception.h"
#include <d3d12.h>
#include <string>

namespace killme
{
    /** Direct3D relational exception */
    class Direct3DException : public Exception
    {
    public:
        /** Constructs with a message */
        explicit Direct3DException(const std::string& msg) : Exception(msg) {}
    };

    /** Returns a default heap properties */
    D3D12_HEAP_PROPERTIES getD3DDefaultHeapProps();

    /** Returns an upload heap properties */
    D3D12_HEAP_PROPERTIES getD3DUploadHeapProps();

    /** Returns a resource description of buffers */
    D3D12_RESOURCE_DESC describeD3DBuffer(size_t size);

    /** Returns a resource description of 2D textures */
    D3D12_RESOURCE_DESC describeD3DTex2D(size_t width, size_t height, DXGI_FORMAT format, D3D12_RESOURCE_FLAGS flags);
}

#endif
