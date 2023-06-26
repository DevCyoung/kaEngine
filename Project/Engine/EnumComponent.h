#pragma once
#include <string>

class Component;

enum class eComponentType 
{
	Camera,
	MeshRenderer,
	Tanning,
	Transform,
	End,
	ScriptComponent
};

const wchar_t* GetComponentName(const eComponentType type);
Component* CreateComponentByName(const std::wstring& componentName);
Component * CreateComponentByEnum(const eComponentType type);

