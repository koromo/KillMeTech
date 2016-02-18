#include "shader.h"
#include <cstring>

namespace killme
{
    ConstantBufferDescription::ConstantBufferDescription(ID3D12ShaderReflectionConstantBuffer* reflection, size_t registerSlot)
        : name_()
        , registerSlot_(registerSlot)
        , size_()
        , variables_()
    {
        // Get the description
        D3D12_SHADER_BUFFER_DESC desc;
        enforce<Direct3DException>(
            SUCCEEDED(reflection->GetDesc(&desc)),
            "Faild to get the description of the constant buffer.");

        name_ = desc.Name;
        size_ = desc.Size;

        // Store descriptions of the variable
        for (UINT i = 0; i < desc.Variables; ++i)
        {
            const auto d3dVarRef = reflection->GetVariableByIndex(i);

            D3D12_SHADER_VARIABLE_DESC d3dVarDesc;
            enforce<Direct3DException>(
                SUCCEEDED(d3dVarRef->GetDesc(&d3dVarDesc)),
                "Faild to get a description of the constant variable.");

            VariableDescription varDesc;
            varDesc.size = d3dVarDesc.Size;
            varDesc.offset = d3dVarDesc.StartOffset;

            if (d3dVarDesc.DefaultValue != NULL)
            {
                const auto p = new unsigned char[d3dVarDesc.Size];
                std::memcpy(p, d3dVarDesc.DefaultValue, d3dVarDesc.Size);
                varDesc.defaultValue = std::shared_ptr<const unsigned char>(p, std::default_delete<const unsigned char[]>());
            }

            variables_.emplace(d3dVarDesc.Name, varDesc);
        }
    }

    std::string ConstantBufferDescription::getName() const
    {
        return name_;
    }

    size_t ConstantBufferDescription::getSize() const
    {
        return size_;
    }

    size_t ConstantBufferDescription::getRegisterSlot() const
    {
        return registerSlot_;
    }

    Optional<VariableDescription> ConstantBufferDescription::describeVariable(const std::string& name) const
    {
        const auto it = variables_.find(name);
        if (it == std::cend(variables_))
        {
            return nullopt;
        }
        return it->second;
    }

    BasicShader::BasicShader(ID3DBlob* byteCode)
        : byteCode_(makeComUnique(byteCode))
        , reflection_()
        , desc_()
    {
        // Get the reflection of the shader
        ID3D12ShaderReflection* reflection;
        enforce<Direct3DException>(
            SUCCEEDED(D3DReflect(byteCode_->GetBufferPointer(), byteCode_->GetBufferSize(), IID_PPV_ARGS(&reflection))),
            "Failed to get the reflection of the shader.");
        reflection_ = makeComUnique(reflection);

        // Get the description of the shader
        enforce<Direct3DException>(
            SUCCEEDED(reflection->GetDesc(&desc_)),
            "Failed to get the description of the shader.");
    }

    const void* BasicShader::getByteCode() const
    {
        return byteCode_->GetBufferPointer();
    }

    size_t BasicShader::getByteCodeSize() const
    {
        return byteCode_->GetBufferSize();
    }
}