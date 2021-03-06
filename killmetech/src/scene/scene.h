#ifndef _KILLME_SCENE_H_
#define _KILLME_SCENE_H_

#include "../renderer/renderstate.h"
#include "../core/math/color.h"
#include <memory>
#include <unordered_set>

namespace killme
{
    class RenderSystem;
    class RenderDevice;
    class Camera;
    class Light;
    class MeshInstance;
    struct FrameResource;

    /** Render scene */
    class Scene
    {
    private:
        std::shared_ptr<RenderDevice> device_;
        ScissorRect scissorRect_;
        Color ambientLight_;
        std::unordered_set<std::shared_ptr<Light>> dirLights_;
        std::unordered_set<std::shared_ptr<Light>> pointLights_;
        std::unordered_set<std::shared_ptr<Camera>> cameras_;
        std::unordered_set<std::shared_ptr<MeshInstance>> meshInstances_;
        std::shared_ptr<Camera> mainCamera_;

    public:
        /** Construct */
        explicit Scene(RenderSystem& renderSystem);

        /** Set the ambient light */
        void setAmbientLight(const Color& c);

        /** Add a light */
        void addLight(const std::shared_ptr<Light>& light);

        /** Remove a light */
        void removeLight(const std::shared_ptr<Light>& light);

        /** Set the main camera */
        void setMainCamera(const std::shared_ptr<Camera>& camera);

        /** Return the main camera */
        std::shared_ptr<Camera> getMainCamera();

        /** Add a camera */
        void addCamera(const std::shared_ptr<Camera>& camera);

        /** Remove a camera */
        void removeCamera(const std::shared_ptr<Camera>& camera);

        /** Add a mesh instance */
        void addMeshInstance(const std::shared_ptr<MeshInstance>& inst);

        /** Remove a mesh instance */
        void removeMeshInstance(const std::shared_ptr<MeshInstance>& inst);

        /** Draw the current scene */
        void renderScene(const FrameResource& frame);
    };
}

#endif
