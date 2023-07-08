#include "pch.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "TimeManager.h"
#include "MessageManager.h"
#include "InputManager.h"
#include "PathManager.h"
#include "ResourceManager.h"
#include "SceneManager.h"
#include "RenderTargetRenderer.h"

Engine::Engine(const HWND hWnd, const UINT renderTargetWidth, const UINT renderTargetHeight)
	: mHwnd(hWnd)
	, mRenderTargetWidth(renderTargetWidth)
	, mRenderTargetHeight(renderTargetHeight)
	, mWindowScreenWidth(renderTargetWidth)
	, mWindowScreenHeight(renderTargetHeight)
	, mGraphicDevice(new GraphicDeviceDX11(mHwnd, mRenderTargetWidth, mRenderTargetHeight))
	, mRenderTargetRenderer(nullptr)
{
	setWindowSize(mRenderTargetWidth, mRenderTargetHeight);
}

Engine::~Engine()
{
	SceneManager::deleteInstance();
	ResourceManager::deleteInstance();
	InputManager::deleteInstance();
	PathManager::deleteInstance();
	MessageManager::deleteInstance();
	TimeManager::deleteInstance();

	SAFE_DELETE_POINTER(mRenderTargetRenderer);
	SAFE_DELETE_POINTER(mGraphicDevice);
}

void Engine::initialize(const HWND hWnd, const UINT renderTargetWidth, const UINT renderTargetHeight)
{
	Assert(hWnd, WCHAR_IS_NULLPTR);
	Assert(!sInstance, WCHAR_IS_NOT_NULLPTR);

	sInstance = new Engine(hWnd, renderTargetWidth, renderTargetHeight);

	TimeManager::initialize();
	MessageManager::initialize();
	PathManager::initialize();
	InputManager::initialize();
	ResourceManager::initialize();
	SceneManager::initialize();

	sInstance->mRenderTargetRenderer = new RenderTargetRenderer();
}

void Engine::run()
{
	updateWindowInfo();

	update();

	lateUpdate();

	render();

	eventUpdate();
}

void Engine::updateWindowInfo()
{
	Assert(mHwnd, WCHAR_IS_NULLPTR);

	RECT windowRect;
	GetClientRect(mHwnd, &windowRect);

	mWindowScreenWidth = windowRect.right - windowRect.left;
	mWindowScreenHeight = windowRect.bottom - windowRect.top;
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
	constexpr FLOAT BG_COLOR[4] = { 0.4f, 0.4f, 0.4f, 1.f };

	mRenderTargetRenderer->Render(mRenderTargetWidth,
		mRenderTargetHeight,
		BG_COLOR,
		mGraphicDevice->GetRenderTargetViewAddressOf(),
		mGraphicDevice->GetDepthStencilView());

	mGraphicDevice->present();
}

void Engine::eventUpdate()
{
	SceneManager::GetInstance()->eventUpdate();
	MessageManager::GetInstance()->eventUpdate(mHwnd);
}

void Engine::setWindowSize(const UINT windowScreenWidth, const UINT windowScreenHeight)
{
	Assert(mHwnd, WCHAR_IS_NULLPTR);

	RECT windowSize =
	{
		0, 0,
		static_cast<LONG>(windowScreenWidth), static_cast<LONG>(windowScreenHeight)
	};

	const BOOL bMENU = GetMenu(mHwnd) != nullptr;

	AdjustWindowRect(&windowSize, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, bMENU);

	const int ADJUST_WIDTH = static_cast<int>(windowSize.right - windowSize.left);
	const int ADJUST_HEIGHT = static_cast<int>(windowSize.bottom - windowSize.top);

	const int LEFT_X_POS = GetSystemMetrics(SM_CXSCREEN) / 2 - static_cast<int>(ADJUST_WIDTH) / 2;
	const int LEFT_Y_POS = GetSystemMetrics(SM_CYSCREEN) / 2 - static_cast<int>(ADJUST_HEIGHT) / 2;

	SetWindowPos(mHwnd, nullptr,
		LEFT_X_POS, LEFT_Y_POS,
		ADJUST_WIDTH, ADJUST_HEIGHT, 0);

	ShowWindow(mHwnd, true);
	UpdateWindow(mHwnd);
}
