#include "pch.h"
#include "RenderComponent.h"
#include "RenderTargetRenderer.h"

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
	Assert(mRenderTargetRenderer, WCHAR_IS_NULLPTR);

	mRenderTargetRenderer->registerRenderComponent(this);
}

void RenderComponent::lateUpdate()
{
}
