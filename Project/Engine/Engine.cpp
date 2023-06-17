#include "pch.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "TimeManager.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "InputManager.h"
#include "SceneManager.h"



namespace engine
{
	Engine::Engine()
		: mGraphicDevice(nullptr)		
		, mHwnd(nullptr)
		, mScreenWidth(static_cast<UINT>(-1))
		, mScreenHeight(static_cast<UINT>(-1))		
	{
	}

	Engine::~Engine()
	{		
		SceneManager::deleteInstance();
		InputManager::deleteInstance();		
		TimeManager::deleteInstance();
		ResourceManager::deleteInstance();
		PathManager::deleteInstance();
	}

	void Engine::initialize(const HWND hWnd, const UINT screenWidth, const UINT screenHeight)
	{
		assert(!sInstance);
		sInstance = new Engine();
		
		PathManager::initialize();
		ResourceManager::initialize();
		
		sInstance->setWindow(hWnd, screenWidth, screenHeight);
		sInstance->mGraphicDevice = std::make_unique<graphics::GraphicDeviceDX11>(hWnd, 
			screenWidth, screenHeight);
		
		TimeManager::initialize();
		InputManager::initialize();
		SceneManager::initialize();

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

	void Engine::render()
	{
		TimeManager::GetInstance()->render(mHwnd);

		mGraphicDevice->clearRenderTarget(mScreenWidth, mScreenHeight);
		SceneManager::GetInstance()->render();
		mGraphicDevice->present();
	}

	void Engine::setWindow(const HWND hwnd, const UINT width, const UINT height)
	{
		mHwnd = hwnd;
		mScreenWidth = width;
		mScreenHeight = height;

		RECT wdScreen = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
		AdjustWindowRect(&wdScreen, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(mHwnd,
			nullptr, 0, 0,
			wdScreen.right - wdScreen.left,
			wdScreen.bottom - wdScreen.top, 0);

		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}
