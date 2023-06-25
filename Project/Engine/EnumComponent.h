#pragma once

namespace engine
{
enum class eComponentType 
{
	Camera,
	MeshRenderer,
	Transform,
	End,
	Script
};

const wchar_t* GetComponentName(const eComponentType type);
Component* CreateComponentByName(const std::wstring& componentName);
Component * CreateComponentByEnum(const eComponentType type);
}

