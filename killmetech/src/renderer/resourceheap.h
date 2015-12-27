#ifndef _KILLME_RESOURCEHEAP_H_
#define _KILLME_RESOURCEHEAP_H_

#include "../windows/winsupport.h"
#include <d3d12.h>
#include <memory>

namespace killme
{
    class ConstantBuffer;

    /// TODO: Now, Resource heap used by only constant buffer
    /** Resource heap */
    class ResourceHeap
    {
    private:
        ComUniquePtr<ID3D12DescriptorHeap> heap_;
        D3D12_DESCRIPTOR_HEAP_TYPE type_;

    public:
        /** Construct with Direct3D descriptor heap */
        ResourceHeap(ID3D12DescriptorHeap* heap, D3D12_DESCRIPTOR_HEAP_TYPE type);

        /** Returns Direct3D descriptor heap type */
        D3D12_DESCRIPTOR_HEAP_TYPE getType() const;

        /** Returns Direct3D descriptor heap */
        ID3D12DescriptorHeap* getD3DHeap();
    };
}

#endif