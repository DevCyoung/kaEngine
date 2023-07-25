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
	static Material* Default2D(const eRenderPriorityType renderPriorityType, 
		const std::wstring& shaderKey, const eResTexture textureType);

	static Material* Sprite2D(const eRenderPriorityType renderPriorityType, const eResTexture textureType);
	static Material* UI2D(const eRenderPriorityType renderPriorityType, const eResTexture textureType);
	static Material* Animation2D(const eRenderPriorityType renderPriorityType, const eResTexture textureType);
};

