#pragma once
#include "EnumConponent.h"

namespace engine
{
	template <typename T, typename Enable = void>
	struct enable_if_component
	{
		static constexpr bool faile = true;
	};

	template <>
	struct enable_if_component<Transform>
	{
		static constexpr eComponentType type = eComponentType::Transform;
	};

	template <>
	struct enable_if_component<Animator>
	{
		static constexpr eComponentType type = eComponentType::Animator;
	};

	template <>
	struct enable_if_component<MeshRenderer>
	{
		static constexpr eComponentType type = eComponentType::MeshRenderer;
	};
}
