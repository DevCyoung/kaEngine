#pragma once
#include "EngineComponentTrait.h"
#include "ScriptComponentTrait.h"

template <typename T>
struct is_component_type
{
	static constexpr bool value = (engine_component_type<T>::value || script_component_type<T>::value);
};
