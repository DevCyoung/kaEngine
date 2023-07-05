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

Engine::Engine(const HWND H_WND, const UINT RENDER_TARGET_WIDTH, const UINT RENDER_TARGET_HEIGHT)
	: mHwnd(H_WND)
	, mRenderTargetWidth(RENDER_TARGET_WIDTH)
	, mRenderTargetHeight(RENDER_TARGET_HEIGHT)
	, mGraphicDevice(new GraphicDeviceDX11(mHwnd, mRenderTargetWidth, mRenderTargetHeight))
	, mRenderTargetRenderer(nullptr)
{
	setWindowSize(mRenderTargetWidth, mRenderTargetHeight);
	updateWindowScreenSize();
	
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

void Engine::initialize(const HWND H_WND, const UINT RENDER_TARGET_WIDTH, const UINT RENDER_TARGET_HEIGHT)
{
	Assert(H_WND, WCHAR_IS_NULLPTR);
	Assert(!sInstance, WCHAR_IS_NOT_NULLPTR);

	sInstance = new Engine(H_WND, RENDER_TARGET_WIDTH, RENDER_TARGET_HEIGHT);

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
	updateWindowScreenSize();

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
	constexpr FLOAT BG_COLOR[4] = { 0.4f, 0.4f, 0.4f, 1.f };

	mRenderTargetRenderer->Render(mRenderTargetWidth,
		mRenderTargetHeight,
		BG_COLOR,
		mGraphicDevice->GetRenderTargetView(),
		mGraphicDevice->GetDepthStencilView());

	mGraphicDevice->present();

	MessageManager::GetInstance()->render(mHwnd);
}

void Engine::updateWindowScreenSize()
{
	Assert(mHwnd, WCHAR_IS_NULLPTR);

	RECT windowRect;
	GetClientRect(mHwnd, &windowRect);

	mWindowScreenWidth = windowRect.right - windowRect.left;
	mWindowScreenHeight = windowRect.bottom - windowRect.top;
}


void Engine::setWindowSize(const UINT WINDOW_SCREEN_WIDTH, const UINT WINDOW_SCREEN_HEIGHT)
{
	Assert(mHwnd, WCHAR_IS_NULLPTR);

	RECT windowSize =
	{
		0, 0,
		static_cast<LONG>(WINDOW_SCREEN_WIDTH), static_cast<LONG>(WINDOW_SCREEN_HEIGHT)
	};

	const BOOL bMENU = GetMenu(mHwnd) != nullptr;

	AdjustWindowRect(&windowSize, WS_CAPTION | WS_SYSMENU | WS_MINIMIZEBOX, bMENU);

	const int ADJUST_WIDTH  = static_cast<int>(windowSize.right - windowSize.left);
	const int ADJUST_HEIGHT = static_cast<int>(windowSize.bottom - windowSize.top);

	//가운데 정렬
	const int LEFT_X_POS = GetSystemMetrics(SM_CXSCREEN) / 2 - static_cast<int>(ADJUST_WIDTH) / 2;
	const int LEFT_Y_POS = GetSystemMetrics(SM_CYSCREEN) / 2 - static_cast<int>(ADJUST_HEIGHT) / 2;

	SetWindowPos(mHwnd, nullptr,
		LEFT_X_POS, LEFT_Y_POS,
		ADJUST_WIDTH, ADJUST_HEIGHT, 0);

	ShowWindow(mHwnd, true);
	UpdateWindow(mHwnd);
}