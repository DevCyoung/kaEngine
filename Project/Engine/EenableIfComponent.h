#pragma once
#include "EnumConponent.h"

namespace engine
{
	template <typename T, bool Enable = true>
	struct enable_if_component
	{
		static constexpr eComponentType type = eComponentType::Script;
	};

	template <>
	struct enable_if_component<Transform>
	{
		static constexpr eComponentType type = eComponentType::Transform;
	};	

	template <>
	struct enable_if_component<Camera>
	{
		static constexpr eComponentType type = eComponentType::Camera;
	};

	template <>
	struct enable_if_component<MeshRenderer>
	{
		static constexpr eComponentType type = eComponentType::MeshRenderer;
	};
}

template <typename T, bool Enable = true>
struct enable_if_script
{
	static constexpr bool fail = false;
};
