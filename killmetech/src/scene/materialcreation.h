#ifndef _KILLME_MATERIALCREATION_H_
#define _KILLME_MATERIALCREATION_H_

#include "material.h"
#include "effectpass.h"
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
    class RenderDevice;
    class ResourceManager;
    enum class ShaderType;

    /** Material parameter description */
    struct MaterialParameterDescription
    {
        TypeNumber type;
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
        LightIteration lightIteration;
        BlendState blendState;
        std::unordered_map<ShaderType, std::string> shaderRef;
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
        MaterialPriority priority_;
        std::unordered_map<std::string, MaterialParameterDescription> paramMap_;
        std::unordered_map<ShaderType, std::unordered_map<std::string, ShaderBoundDescription>> shaderBoundMap_;
        std::vector<std::pair<std::string, TechniqueDescription>> techs_;

    public:
        void setPriority(MaterialPriority priority);
        void addParameter(const std::string& name, MaterialParameterDescription&& desc);
        void addShaderBound(ShaderType type, const std::string& name, ShaderBoundDescription&& desc);
        void addTechnique(const std::string& name, TechniqueDescription&& desc);

        MaterialPriority getPriority() const;

        Optional<TypeNumber> getParameterType(const std::string& name) const;
        bool hasShaderBound(ShaderType type, const std::string& name) const;

        const ShaderBoundDescription& getShaderBound(ShaderType type, const std::string& name) const;

        auto getParameters() const
            -> decltype(constRange(paramMap_))
        {
            return constRange(paramMap_);
        }

        auto getTechniques() const
            -> decltype(constRange(techs_))
        {
            return constRange(techs_);
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
    std::shared_ptr<Material> loadMaterial(RenderDevice& device, ResourceManager& resources, const std::string& path);
}

#endif