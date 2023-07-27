#include "pch.h"
#include "EnumComponent.h"

#include "Animator2D.h"
#include "Camera.h"
#include "CircleCollider2D.h"
#include "Light2D.h"
#include "RectCollider2D.h"
#include "Rigidbody2D.h"
#include "SpriteRenderer.h"
#include "Transform.h"

static constexpr const wchar_t* const ComponentNames[static_cast<UINT>(eComponentType::End)]
{
	L"Animator2D",
	L"Camera",
	L"CircleCollider2D",
	L"Light2D",
	L"RectCollider2D",
	L"Rigidbody2D",
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

	if (L"Animator2D" == componentName)
		component = new Animator2D;
	else if (L"Camera" == componentName)
		component = new Camera;
	else if (L"CircleCollider2D" == componentName)
		component = new CircleCollider2D;
	else if (L"Light2D" == componentName)
		component = new Light2D;
	else if (L"RectCollider2D" == componentName)
		component = new RectCollider2D;
	else if (L"Rigidbody2D" == componentName)
		component = new Rigidbody2D;
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
	case eComponentType::Animator2D:
		component = new Animator2D;
		break;
	case eComponentType::Camera:
		component = new Camera;
		break;
	case eComponentType::CircleCollider2D:
		component = new CircleCollider2D;
		break;
	case eComponentType::Light2D:
		component = new Light2D;
		break;
	case eComponentType::RectCollider2D:
		component = new RectCollider2D;
		break;
	case eComponentType::Rigidbody2D:
		component = new Rigidbody2D;
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

