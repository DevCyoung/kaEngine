#pragma once
#include <memory>
#include <assert.h>
#include "Singleton.h"

class GraphicDeviceDX11;
class RenderTargetRenderer;

class Engine
{
	friend int APIENTRY::wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
		LPWSTR lpCmdLine, int nCmdShow);
	SINGLETON_DECLARE(Engine);

private:
	Engine(const HWND H_WND, const UINT RENDER_TARGET_WIDTH, const UINT RENDER_TARGET_HEIGHT);

public:
	Vector2 GetRenderTargetSize() const  
	{  
		return Vector2(static_cast<float>(mRenderTargetWidth), static_cast<float>(mRenderTargetHeight));
	}

	Vector2 GetWindowScreenSize() const
	{
		return Vector2(static_cast<float>(mWindowScreenWidth), static_cast<float>(mWindowScreenHeight));
	}

	HWND GetHwnd() const { Assert(mHwnd, WCHAR_IS_NULLPTR); return mHwnd; }
	GraphicDeviceDX11* GetGraphicDevice() const { return mGraphicDevice; }

	//FIXME
	RenderTargetRenderer* GetRenderTargetRenderer() const
	{
		Assert(mRenderTargetRenderer, WCHAR_IS_NULLPTR);

		return mRenderTargetRenderer;
	}

private:
	static void initialize(const HWND H_WND, const UINT RENDER_TARGET_WIDTH, const UINT RENDER_TARGET_HEIGHT);
	void setWindowSize(const UINT WINDOW_SCREEN_WIDTH, const UINT WINDOW_SCREEN_HEIGHT);
	void updateWindowScreenSize();

	void run();
	void update();
	void lateUpdate();
	void render();

private:
	HWND mHwnd;
	UINT mRenderTargetWidth;
	UINT mRenderTargetHeight;
	UINT mWindowScreenWidth;
	UINT mWindowScreenHeight;

	GraphicDeviceDX11* mGraphicDevice;
	RenderTargetRenderer* mRenderTargetRenderer;
};

#define gEngine Engine::GetInstance()
#define gGraphicDevice gEngine->GetGraphicDevice()