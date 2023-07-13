#include "pch.h"
#include "SceneManager.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

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
	scene->initialize();
}

void SceneManager::update()
{
	mCurrentScene->update();
}

void SceneManager::lateUpdate()
{
	mCurrentScene->lateUpdate();
}

void SceneManager::eventUpdate()
{
	mCurrentScene->eventUpdate();
}

void SceneManager::render(const UINT renderTargetWidth,
	const UINT renderTargetHeight,
	const FLOAT backgroundColor[4],
	ID3D11RenderTargetView** const ppRenderTargetView,
	ID3D11DepthStencilView* const depthStencilView)
{
	gGraphicDevice->ClearRenderTarget(ppRenderTargetView,
		depthStencilView,
		backgroundColor);

	mCurrentScene->render(renderTargetWidth,
		renderTargetHeight,		
		ppRenderTargetView,
		depthStencilView);

	mCurrentScene->renderFlush();
}
