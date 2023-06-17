#pragma once	

#include "EnumResourceTypeTexture.h"
#include "EnumResourceTypeMesh.h"
#include "EnumResourceTypeMaterial.h"
#include "EnumResourceTypeShader.h"
#include "EnumResourceTypeAnimation.h"
#include "EnumResourceTypeFont.h"
#include "EnumResourceTypeSound.h"
#include "EnumResourceTypeLevel.h"


namespace engine
{
	class Texture;
	class Mesh;
	class Material;
	class Shader;
	class Animation;
	class Font;
	class Sound;
	class Level;


	enum class eResourceType
	{
		Texture,
		Mesh,
		Material,
		Shader,
		Animation,
		Font,
		Sound,
		Level,
		End
	};	
}

namespace engine
{
	template <typename T, typename Enable = void>
	struct enable_if_resource
	{
		static constexpr bool faile = true;
	};

	template <>
	struct enable_if_resource<Texture>
	{
		static constexpr eResourceType resourceType = eResourceType::Texture;
		using ResEnumType = eResTexture;
	};

	template <>
	struct enable_if_resource<Mesh>
	{
		static constexpr eResourceType resourceType = eResourceType::Mesh;
		using ResEnumType = eResMesh;
	};

	template <>
	struct enable_if_resource<Material>
	{
		static constexpr eResourceType resourceType = eResourceType::Material;
		using ResEnumType = eResMaterial;
	};

	template <>
	struct enable_if_resource<Shader>
	{
		static constexpr eResourceType resourceType = eResourceType::Shader;
		using ResEnumType = eResShader;
	};

	template <>
	struct enable_if_resource<Animation>
	{
		static constexpr eResourceType resourceType = eResourceType::Animation;
		using ResEnumType = eResAnimation;
	};

	template <>
	struct enable_if_resource<Font>
	{
		static constexpr eResourceType resourceType = eResourceType::Font;
		using ResEnumType = eResFont;
	};

	template <>
	struct enable_if_resource<Sound>
	{
		static constexpr eResourceType resourceType = eResourceType::Sound;
		using Restype = eResSound;
	};

	template <>
	struct enable_if_resource<Level>
	{
		static constexpr eResourceType resourceType = eResourceType::Level;
		using ResEnumType = eResLevel;
	};
}
