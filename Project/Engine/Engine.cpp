#include "pch.h"
#include "Engine.h"

#include "GraphicDeviceDx11.h"
#include "CBCollection.h"

#include "TimeManager.h"
#include "InputManager.h"
#include "SceneManager.h"
#include "ConstantBufferManager.h"


namespace engine
{
	Engine::Engine()
		: mGraphicDevice(nullptr)
		, mCBCollection()
		, mHwnd(nullptr)
		, mWidth(static_cast<UINT>(-1))
		, mHeight(static_cast<UINT>(-1))
		, mbInitialize(false)
	{
	}

	Engine::~Engine()
	{
		//ConstantBufferManager::deleteInstance();
		TimeManager::deleteInstance();
		InputManager::deleteInstance();
		SceneManager::deleteInstance();
	}

	ID3D11Device* Engine::GetDevice() const
	{
		return mGraphicDevice->mDevice.Get();
	}

	ID3D11DeviceContext* Engine::GetContext() const
	{
		return mGraphicDevice->mContext.Get();
	}

	graphics::GraphicDeviceDX11* Engine::GetGraphicDevice() const
	{
		return mGraphicDevice.get();
	}

	void Engine::initialize(const HWND hwnd, const UINT width, const UINT height)
	{
		assert(!sInstance);
		sInstance = new Engine();

		sInstance->setWindow(hwnd, width, height);

		sInstance->mGraphicDevice = std::make_unique<graphics::GraphicDeviceDX11>();
		sInstance->mCBCollection = std::make_unique<CBCollection>();

		//ConstantBufferManager::initialize();
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
		InputManager::GetInstance()->update();
		SceneManager::GetInstance()->update();
	}

	void Engine::lateUpdate()
	{
		SceneManager::GetInstance()->lateUpdate();
	}

	void Engine::render()
	{
		TimeManager::GetInstance()->render();

		mGraphicDevice->clearRenderTarget();
		SceneManager::GetInstance()->render();
		mGraphicDevice->present();
	}

	void Engine::setWindow(const HWND hwnd, const UINT width, const UINT height)
	{
		mHwnd = hwnd;
		mWidth = width;
		mHeight = height;

		RECT wdScreen = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
		AdjustWindowRect(&wdScreen, WS_OVERLAPPEDWINDOW, FALSE);
		SetWindowPos(mHwnd,
			nullptr /*HWND_TOP*/, 0, 0,
			wdScreen.right - wdScreen.left,
			wdScreen.bottom - wdScreen.top, 0/*SWP_NOMOVE | SWP_NOZORDER*/);

		ShowWindow(mHwnd, true);
		UpdateWindow(mHwnd);
	}
}