#pragma once
#include <string>

class Component;

enum class eComponentType 
{
	Animator2D,
	Camera,
	CircleCollider2D,
	Light2D,
	ParticleSystem,
	RectCollider2D,
	Rigidbody2D,
	SpriteRenderer,
	Transform,
	End,
	ScriptComponent
};

const wchar_t* GetComponentName(const eComponentType type);
Component* CreateComponentByName(const std::wstring& componentName);
Component * CreateComponentByEnum(const eComponentType type);

