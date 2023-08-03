#include "pch.h"
#include "EnumComponent.h"

#include "Transform.h"
#include "Animator2D.h"
#include "Camera.h"
#include "CircleCollider2D.h"
#include "Light2D.h"
#include "LineCollider2D.h"
#include "ParticleSystem.h"
#include "RectCollider2D.h"
#include "Rigidbody2D.h"
#include "SpriteRenderer.h"

static constexpr const wchar_t* const ComponentNames[static_cast<UINT>(eComponentType::End)]
{
	L"Transform",
	L"Animator2D",
	L"Camera",
	L"CircleCollider2D",
	L"Light2D",
	L"LineCollider2D",
	L"ParticleSystem",
	L"RectCollider2D",
	L"Rigidbody2D",
	L"SpriteRenderer",
};

const wchar_t* GetComponentName(const eComponentType type)
{
	assert(static_cast<UINT>(type) < static_cast<UINT>(eComponentType::End));
	return ComponentNames[static_cast<UINT>(type)];
}

Component* CreateComponentByName(const std::wstring& componentName)
{
	Component* component = nullptr;

	if (L"Transform" == componentName)
		component = new Transform;
	else if (L"Animator2D" == componentName)
		component = new Animator2D;
	else if (L"Camera" == componentName)
		component = new Camera;
	else if (L"CircleCollider2D" == componentName)
		component = new CircleCollider2D;
	else if (L"Light2D" == componentName)
		component = new Light2D;
	else if (L"LineCollider2D" == componentName)
		component = new LineCollider2D;
	else if (L"ParticleSystem" == componentName)
		component = new ParticleSystem;
	else if (L"RectCollider2D" == componentName)
		component = new RectCollider2D;
	else if (L"Rigidbody2D" == componentName)
		component = new Rigidbody2D;
	else if (L"SpriteRenderer" == componentName)
		component = new SpriteRenderer;
	else
		assert(false);
	return component;
}

Component* CreateComponentByEnum(const eComponentType type)
{
	Component* component = nullptr;

	switch (type)
	{
	case eComponentType::Transform:
		component = new Transform;
		break;
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
	case eComponentType::LineCollider2D:
		component = new LineCollider2D;
		break;
	case eComponentType::ParticleSystem:
		component = new ParticleSystem;
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
	default:
		assert(false);
		break;
	}
	return component;
}

