#pragma once
#include <Engine/EenableIfComponent.h>
#include "EnumScript.h"

template <>
struct enable_if_script<SampleScript>
{
	static constexpr eScriptType type = eScriptType::SampleScript;
};

template <>
struct enable_if_script<CameraScript>
{
	static constexpr eScriptType type = eScriptType::CameraScript;
};