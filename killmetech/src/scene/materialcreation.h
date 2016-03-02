#ifndef _KILLME_MATERIALCREATION_H_
#define _KILLME_MATERIALCREATION_H_

#include "../renderer/renderstate.h"
#include "../core/utility.h"
#include "../core/variant.h"
#include "../core/optional.h"
#include "../core/exception.h"
#include <unordered_map>
#include <map>
#include <vector>
#include <utility>
#include <set>
#include <string>
#include <memory>

namespace killme
{
    class Material;
    class RenderSystem;
    class ResourceManager;

    /** Material parameter description */
    struct MaterialParameterDescription
    {
        TypeTag type;
        Variant value;
    };

    /** Shader bound description */
    struct ShaderBoundDescription
    {
        std::string path;
        std::unordered_map<std::string, std::string> constantMapping; // shader constant -> material param
        std::unordered_map<std::string, std::string> textureMapping; // shader texture -> material param
        std::unordered_map<std::string, std::string> samplerMapping; // shader sampler -> material param
    };

    /** Pass description */
    struct PassDescription
    {
        bool forEachLight;
        BlendState blendState;
        std::string vsRef;
        std::string psRef;
    };

    /** Technique description */
    struct TechniqueDescription
    {
        std::map<size_t, PassDescription> passes;
    };

    /** Result of parsing .material file */
    class MaterialDescription
    {
    private:
        std::unordered_map<std::string, MaterialParameterDescription> paramMap_;
        std::unordered_map<std::string, ShaderBoundDescription> vsBoundMap_;
        std::unordered_map<std::string, ShaderBoundDescription> psBoundMap_;
        std::vector<std::pair<std::string, TechniqueDescription>> techs_;

    public:
        void addParameter(const std::string& name, MaterialParameterDescription&& desc);
        void addVShaderBound(const std::string& name, ShaderBoundDescription&& desc);
        void addPShaderBound(const std::string& name, ShaderBoundDescription&& desc);
        void addTechnique(const std::string& name, TechniqueDescription&& desc);

        Optional<TypeTag> getParameterType(const std::string& name) const;
        bool hasVShaderBound(const std::string& name) const;
        bool hasPShaderBound(const std::string& name) const;

        const ShaderBoundDescription& getVShaderBound(const std::string& name) const;
        const ShaderBoundDescription& getPShaderBound(const std::string& name) const;

        auto getParameters() const
            -> decltype(makeRange(paramMap_))
        {
            return makeRange(paramMap_);
        }

        auto getTechniques() const
            -> decltype(makeRange(techs_))
        {
            return makeRange(techs_);
        }
    };

    /** Loading material exception */
    class MaterialLoadException : public FileException
    {
    public:
        /** Construct */
        explicit MaterialLoadException(const std::string& msg);
    };

    /** Load a material */
    std::shared_ptr<Material> loadMaterial(const std::shared_ptr<RenderSystem>& renderSystem, ResourceManager& resourceManager, const std::string& path);
}

#endif