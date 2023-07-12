#include "pch.h"
#include "SceneManager.h"

SceneManager::SceneManager()
	: mCurrentScene(nullptr)
{
}

SceneManager::~SceneManager()
{
	DELETE_POINTER(mCurrentScene);
}

void SceneManager::LoadScene(Scene* const scene)
{
	Assert(scene, WCHAR_IS_NULLPTR);
	DELETE_ARRAY(sInstance->mCurrentScene);

	mCurrentScene = scene;
	scene->Initialize();
}

void SceneManager::update()
{
	mCurrentScene->Update();
}

void SceneManager::lateUpdate()
{
	mCurrentScene->LateUpdate();
}

void SceneManager::eventUpdate()
{
	mCurrentScene->EventUpdate();
}

void SceneManager::render(const UINT renderTargetWidth,
	const UINT renderTargetHeight,
	const FLOAT backgroundColor[4],
	ID3D11RenderTargetView** const ppRenderTargetView,
	ID3D11DepthStencilView* const depthStencilView)
{
	mCurrentScene->Render(renderTargetWidth,
		renderTargetHeight,
		backgroundColor,
		ppRenderTargetView,
		depthStencilView);

	mCurrentScene->RenderFlush();
}