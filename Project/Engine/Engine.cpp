#include "pch.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "TimeManager.h"
#include "RenderTargetRenderer.h"
#include "MessageManager.h"
#include "InputManager.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "EventManager.h"
#include "RenderTargetRenderer.h"

Engine::Engine(const HWND hWnd, const UINT screenWidth, const UINT screenHeight)
	: mHwnd(hWnd)
	, mScreenWidth(screenWidth)
	, mScreenHeight(screenHeight)
	, mGraphicDevice(new GraphicDeviceDX11(hWnd, mScreenWidth, mScreenHeight))
	, mRenderTargetRenderer(new RenderTargetRenderer())
{
	TimeManager::initialize();
	MessageManager::initialize();
	PathManager::initialize();
	InputManager::initialize();
	ResourceManager::initialize();
	SceneManager::initialize();
	//EventManager::initialize();
}

Engine::~Engine()
{
	//EventManager::deleteInstance();
	SceneManager::deleteInstance();
	ResourceManager::deleteInstance();
	InputManager::deleteInstance();
	PathManager::deleteInstance();
	MessageManager::deleteInstance();
	TimeManager::deleteInstance();

	SAFE_DELETE_POINTER(mRenderTargetRenderer);
	SAFE_DELETE_POINTER(mGraphicDevice);
}

void Engine::initialize(const HWND hWnd, const UINT screenWidth, const UINT screenHeight)
{
	Assert(hWnd, WCHAR_IS_NULLPTR);
	Assert(!sInstance, WCHAR_IS_NOT_NULLPTR);

	sInstance = new Engine(hWnd, screenWidth, screenHeight);
}

void Engine::run()
{
	update();

	lateUpdate();

	render();
}

void Engine::update()
{
	TimeManager::GetInstance()->update();
	InputManager::GetInstance()->update(mHwnd);
	SceneManager::GetInstance()->update();
}

void Engine::lateUpdate()
{
	SceneManager::GetInstance()->lateUpdate();
}

#include "EngineMath.h"

void Engine::render()
{
	const float r = helper::LerpSinBtwZeroAndOne(TimeManager::GetInstance()->GetGlobalTime() * 4.f);
	const float g = helper::LerpCosBtwZeroAndOne(TimeManager::GetInstance()->GetGlobalTime() * 4.f);
	const float b = helper::LerpSinBtwZeroAndOne(TimeManager::GetInstance()->GetGlobalTime() * 4.f);

	const FLOAT bgColor[4] = { r, g, b, 1.f };

	mRenderTargetRenderer->Render(mScreenWidth,
		mScreenHeight,
		bgColor,
		mGraphicDevice->GetRenderTargetView(),
		mGraphicDevice->GetDepthStencilView());

	mGraphicDevice->present();

	MessageManager::GetInstance()->render(mHwnd);
}
