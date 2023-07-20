#include "pch.h"
#include "GameSystem.h"
#include "Physics2D.h"
#include "RenderTargetRenderer.h"

GameSystem::GameSystem(Scene* const scene)
	: mScene(scene)
	, mPhysics2D(new Physics2D(scene))
	, mRenderTargetRenderer(new RenderTargetRenderer())
{
}

GameSystem::~GameSystem()
{
	SAFE_DELETE_POINTER(mRenderTargetRenderer);
	SAFE_DELETE_POINTER(mPhysics2D);
}
