#include "pch.h"
#include "RenderComponent.h"
#include "RenderTargetRenderer.h"
#include "GameObject.h"
#include "GameSystem.h"


RenderComponent::RenderComponent(const eComponentType componentType)
	: Component(componentType)
	, mMesh(nullptr)
	, mMaterial(nullptr)
{
}

RenderComponent::~RenderComponent()
{
}

void RenderComponent::initialize()
{
}

void RenderComponent::update()
{
	if (GetOwner()->GetState() == GameObject::eState::Active)
	{
		GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->registerRenderComponent(this);
	}	
}

void RenderComponent::lateUpdate()
{
}
