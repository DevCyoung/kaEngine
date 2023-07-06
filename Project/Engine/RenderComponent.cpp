#include "pch.h"
#include "RenderComponent.h"
#include "RenderTargetRenderer.h"

RenderComponent::RenderComponent(const eComponentType COMPONENT_TYPE)
	: Component(COMPONENT_TYPE)
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

	mRenderTargetRenderer->RegisterRenderComponent(this);
}

void RenderComponent::lateUpdate()
{
}
