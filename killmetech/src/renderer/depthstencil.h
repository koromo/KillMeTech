#ifndef _KILLME_DEPTHSTENCIL_H_
#define _KILLME_DEPTHSTENCIL_H_

#include "renderdevice.h"
#include "../windows/winsupport.h"
#include <d3d12.h>
#include <memory>

namespace killme
{
    class Texture;
    enum class PixelFormat;

    /** Depth stencil */
    /// TODO: Not supported stencil buffer
    class DepthStencil : public RenderDeviceChild
    {
    private:
        std::shared_ptr<Texture> tex_;
        D3D12_RESOURCE_DESC desc_;

    public:
        /** Resource location */
        struct Location
        {
            D3D12_CPU_DESCRIPTOR_HANDLE ofD3D;
            DXGI_FORMAT format;
        };

        /** Initialize */
        void initialize(const std::shared_ptr<Texture>& tex);

        /** Create the Direct3D view into a desctipror heap */
        Location locate(ID3D12Device* device, D3D12_CPU_DESCRIPTOR_HANDLE location);
    };

    /** Create depth stencil interface */
    std::shared_ptr<DepthStencil> depthStencilInterface(const std::shared_ptr<Texture>& tex);
}

#endif