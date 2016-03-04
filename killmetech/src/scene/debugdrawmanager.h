#ifndef _KILLME_DEBUGDRAWMANAGER_H_
#define _KILLME_DEBUGDRAWMANAGER_H_

#include "../renderer/renderstate.h"
#include "../core/platform.h"
#include <memory>
#include <vector>

namespace killme
{
    class Vector3;
    class Color;
    class PipelineState;
    class ConstantBuffer;
    class GpuResourceHeap;
    class RenderSystem;
    class Camera;
    struct FrameResource;

#ifdef KILLME_DEBUG

    /** Debug drawer */
    class DebugDrawManager
    {
    private:
        std::vector<Vector3> positions_;
        std::vector<Color> colors_;

        std::shared_ptr<RenderSystem> renderSystem_;
        std::shared_ptr<ConstantBuffer> viewProjBuffer_;
        std::shared_ptr<GpuResourceHeap> viewProjHeap_;
        std::shared_ptr<PipelineState> pipeline_;
        ScissorRect scissorRect_;

    public:
        /** Initialize */
        void startup(const std::shared_ptr<RenderSystem>& renderSystem);

        /** Finalize */
        void shutdown();

        /** Add line */
        void line(const Vector3& from, const Vector3& to, const Color& color);

        /** Clear all debugs */
        void clear();

        /** Draw */
        void debugDraw(const Camera& camera, const FrameResource& frame);
    };

#else

    class DebugDrawManager
    {
    public:
        void startup(const std::shared_ptr<RenderSystem>&) {}
        void shutdown() {}
        void line(const Vector3&, const Vector3&, const Color&) {}
        void clear() {}
        void debugDraw(const Camera&, const FrameResource&) {}
    };

#endif

    extern DebugDrawManager debugDrawManager;
}

#endif