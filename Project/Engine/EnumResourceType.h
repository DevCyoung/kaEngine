#pragma once

namespace engine
{
	class Texture;
	class Mesh;
	class Material;
	class Shader;
	class Animation;
	class Font;
	class Sound;
	class Scene;

	enum class eResTexture;
	enum class eResMesh;
	enum class eResMaterial;
	enum class eResShader;
	enum class eResAnimation;
	enum class eResFont;
	enum class eResSound;
	enum class eResScene;


	enum class eResourceType
	{
		Texture,
		Mesh,
		Material,
		Shader,
		Animation,
		Font,
		Sound,
		Scene,
		End
	};	
}

namespace engine
{
	template <typename T, typename Enable = void>
	struct enable_if_resource
	{		
		static constexpr bool boolType = false;
	};

	template <>
	struct enable_if_resource<Texture>
	{
		using eResEnumType = eResTexture;
		static constexpr eResourceType resourceType = eResourceType::Texture;
	};

	template <>
	struct enable_if_resource<Mesh>
	{
		using eResEnumType = eResMesh;
		static constexpr eResourceType resourceType = eResourceType::Mesh;
	};

	template <>
	struct enable_if_resource<Material>
	{
		using eResEnumType = eResMaterial;
		static constexpr eResourceType resourceType = eResourceType::Material;
	};

	template <>
	struct enable_if_resource<Shader>
	{
		using ResEnueResEnumTypemType = eResShader;
		static constexpr eResourceType resourceType = eResourceType::Shader;
	};

	template <>
	struct enable_if_resource<Animation>
	{
		using eResEnumType = eResAnimation;
		static constexpr eResourceType resourceType = eResourceType::Animation;
	};

	template <>
	struct enable_if_resource<Font>
	{
		using eResEnumType = eResFont;
		static constexpr eResourceType resourceType = eResourceType::Font;
	};

	template <>
	struct enable_if_resource<Sound>
	{
		using eResEnumType = eResSound;
		static constexpr eResourceType resourceType = eResourceType::Sound;
	};

	template <>
	struct enable_if_resource<Scene>
	{
		using eResEnumType = eResScene;
		static constexpr eResourceType resourceType = eResourceType::Scene;
	};
}
