#pragma once


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


template <typename T, typename Enable = void>
struct engine_resource_type
{
	static constexpr bool boolType = false;
};

template <>
struct engine_resource_type<Texture>
{
	using eResEnumType = eResTexture;
	static constexpr eResourceType resourceType = eResourceType::Texture;
};

template <>
struct engine_resource_type<Mesh>
{
	using eResEnumType = eResMesh;
	static constexpr eResourceType resourceType = eResourceType::Mesh;
};

template <>
struct engine_resource_type<Material>
{
	using eResEnumType = eResMaterial;
	static constexpr eResourceType resourceType = eResourceType::Material;
};

template <>
struct engine_resource_type<Shader>
{
	using ResEnueResEnumTypemType = eResShader;
	static constexpr eResourceType resourceType = eResourceType::Shader;
};

template <>
struct engine_resource_type<Animation>
{
	using eResEnumType = eResAnimation;
	static constexpr eResourceType resourceType = eResourceType::Animation;
};

template <>
struct engine_resource_type<Font>
{
	using eResEnumType = eResFont;
	static constexpr eResourceType resourceType = eResourceType::Font;
};

template <>
struct engine_resource_type<Sound>
{
	using eResEnumType = eResSound;
	static constexpr eResourceType resourceType = eResourceType::Sound;
};

template <>
struct engine_resource_type<Scene>
{
	using eResEnumType = eResScene;
	static constexpr eResourceType resourceType = eResourceType::Scene;
};
