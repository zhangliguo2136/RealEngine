#include "Material.h"

TMaterial::TMaterial(const std::string& InName, const std::string& InShaderName)
	:Name(InName), ShaderName(InShaderName)
{

}

TShader* TMaterial::GetShaderByDefines(const TShaderDefines& ShaderDefines)
{
    auto Iter = ShaderMap.find(ShaderDefines);

    if (Iter == ShaderMap.end())
    {
        // Create new shader
        TShaderInfo ShaderInfo;
        ShaderInfo.ShaderName = ShaderName;
        ShaderInfo.FileName = ShaderName;
        ShaderInfo.ShaderDefines = ShaderDefines;
        std::unique_ptr<TShader> NewShader = std::make_unique<TShader>(ShaderInfo);

        ShaderMap.insert({ ShaderDefines, std::move(NewShader) });

        return ShaderMap[ShaderDefines].get();
    }
    else
    {
        return Iter->second.get();
    }
}