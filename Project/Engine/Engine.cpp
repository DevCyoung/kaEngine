#include "pch.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "TimeManager.h"
#include "MessageManager.h"
#include "InputManager.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "EventManager.h"

Engine::Engine(const HWND hWnd, const UINT screenWidth, const UINT screenHeight)
	: mHwnd(hWnd)
	, mScreenWidth(screenWidth)
	, mScreenHeight(screenHeight)
	, mGraphicDevice(new GraphicDeviceDX11(hWnd, mScreenWidth, mScreenHeight))
{
	TimeManager::initialize();
	MessageManager::initialize();
	PathManager::initialize();
	InputManager::initialize();
	ResourceManager::initialize();
	SceneManager::initialize();
	EventManager::initialize();
}

Engine::~Engine()
{
	EventManager::deleteInstance();
	SceneManager::deleteInstance();
	ResourceManager::deleteInstance();
	InputManager::deleteInstance();
	PathManager::deleteInstance();
	MessageManager::deleteInstance();
	TimeManager::deleteInstance();

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
	EventManager::GetInstance()->update();
}

void Engine::lateUpdate()
{
	SceneManager::GetInstance()->lateUpdate();
	EventManager::GetInstance()->lateUpdate();
	MessageManager::GetInstance()->lateUpdate();
}

void Engine::render()
{	
	mGraphicDevice->clearRenderTarget(mScreenWidth, mScreenHeight);
	SceneManager::GetInstance()->render();
	MessageManager::GetInstance()->render(mHwnd);
	mGraphicDevice->present();
}
