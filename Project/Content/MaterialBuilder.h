#pragma once

class Material;

enum class eResTexture;
enum class eRenderPriorityType;

class MaterialBuilder
{
private:
	MaterialBuilder() = delete;
	virtual ~MaterialBuilder() = delete;
	MaterialBuilder(const MaterialBuilder&) = delete;
	MaterialBuilder& operator=(const MaterialBuilder&) = delete;

public:
	static Material* BuildDefault2DMaterial(const eRenderPriorityType renderPriorityType, 
		const std::wstring& shaderKey, const eResTexture textureType);
};

