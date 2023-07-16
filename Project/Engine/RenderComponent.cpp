#include "pch.h"
#include "RenderComponent.h"
#include "RenderTargetRenderer.h"
#include "GameObject.h"

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
	GetOwner()->GetRenderTargetRenderer()->registerRenderComponent(this);
}

void RenderComponent::lateUpdate()
{
}
