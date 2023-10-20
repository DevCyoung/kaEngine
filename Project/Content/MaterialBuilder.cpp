#include "pch.h"
#include "MaterialBuilder.h"
#include "ResourceManager.h"

Material* MaterialBuilder::Default2D(const eRenderPriorityType renderPriorityType, 
	const std::wstring& shaderKey, const eResTexture textureType)
{
		Material* const material = new Material(renderPriorityType);

		material->SetShader(gResourceManager
			->FindOrNull<Shader>(shaderKey));
		material->SetTexture(gResourceManager
			->FindOrNullByEnum<Texture>(textureType));

	return material;
}

Material* MaterialBuilder::Sprite2D(const eRenderPriorityType renderPriorityType, 
	const eResTexture textureType)
{
	return Default2D(renderPriorityType, L"Sprite2D", textureType);
}

Material* MaterialBuilder::UI2D(const eRenderPriorityType renderPriorityType, 
	const eResTexture textureType)
{
	return Default2D(renderPriorityType, L"UI2D", textureType);;
}

Material* MaterialBuilder::Animation2D(const eRenderPriorityType renderPriorityType, 
const eResTexture textureType)
{
	return Default2D(renderPriorityType, L"Animation2D", textureType);
}


Material* MaterialBuilder::LightSprite2D(const eRenderPriorityType renderPriorityType,
	const eResTexture textureType)
{
	Material* const material = new Material(renderPriorityType);

	material->SetShader(gResourceManager
		->FindOrNull<Shader>(L"LightSprite2D"));
	material->SetTexture(gResourceManager
		->FindOrNullByEnum<Texture>(textureType));
	return material;
	
}