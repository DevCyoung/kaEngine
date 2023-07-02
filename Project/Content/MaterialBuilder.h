#pragma once

class Material;

enum class eResTexture;
enum class eRenderType;

class MaterialBuilder
{
private:
	MaterialBuilder() = delete;
	virtual ~MaterialBuilder() = delete;
	MaterialBuilder(const MaterialBuilder&) = delete;
	MaterialBuilder& operator=(const MaterialBuilder&) = delete;

public:
	static Material* BuildDefault2DMaterial(const eRenderType renderType, 
		const std::wstring& shaderName, const eResTexture textureType);
};
