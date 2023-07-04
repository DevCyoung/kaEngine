#include "pch.h"
#include "EnumComponent.h"

#include "Camera.h"
#include "DebugRenderer2D.h"
#include "SpriteRenderer.h"
#include "Transform.h"

static constexpr const wchar_t* const ComponentNames[static_cast<UINT>(eComponentType::End)]
{
	L"Camera",
	L"DebugRenderer2D",
	L"SpriteRenderer",
	L"Transform",
};

const wchar_t* GetComponentName(const eComponentType type)
{
	assert(static_cast<UINT>(type) < static_cast<UINT>(eComponentType::End));
	return ComponentNames[static_cast<UINT>(type)];
}

Component* CreateComponentByName(const std::wstring& componentName)
{
	Component* component = nullptr;

	if (L"Camera" == componentName)
		component = new Camera;
	else if (L"DebugRenderer2D" == componentName)
		component = new DebugRenderer2D;
	else if (L"SpriteRenderer" == componentName)
		component = new SpriteRenderer;
	else if (L"Transform" == componentName)
		component = new Transform;
	else
		assert(false);
	return component;
}

Component* CreateComponentByEnum(const eComponentType type)
{
	Component* component = nullptr;

	switch (type)
	{
	case eComponentType::Camera:
		component = new Camera;
		break;
	case eComponentType::DebugRenderer2D:
		component = new DebugRenderer2D;
		break;
	case eComponentType::SpriteRenderer:
		component = new SpriteRenderer;
		break;
	case eComponentType::Transform:
		component = new Transform;
		break;
	default:
		assert(false);
		break;
	}
	return component;
}

