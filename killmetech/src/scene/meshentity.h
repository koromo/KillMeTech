#ifndef _KILLME_MESHENTITY_H_
#define _KILLME_MESHENTITY_H_

#include "renderqueue.h"
#include "sceneentity.h"
#include "../resources/resource.h"
#include <memory>

namespace killme
{
    class Mesh;
    class Material;
    class MeshRenderer;
    class SceneNode;
    class RenderQueue;
    struct SceneContext;

    /** The meshed model entity */
    class MeshEntity : public SceneEntity
    {
    private:
        Resource<Mesh> mesh_;
        std::shared_ptr<MeshRenderer> renderer_;

    public:
        /** Constructs */
        MeshEntity(const Resource<Mesh>& mesh);

        void collectRenderer(RenderQueue& queue);
    };

    class MeshRenderer : public Renderer
    {
    private:
        std::weak_ptr<SceneNode> node_;
        Resource<Mesh> mesh_;

    public:
        MeshRenderer(const Resource<Mesh>& mesh);
        void setOwnerNode(const std::weak_ptr<SceneNode>& node);
        void recordCommands(const SceneContext& context);
    };
}

#endif