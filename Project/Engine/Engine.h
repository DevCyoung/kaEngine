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
	Engine(const HWND hWnd, const UINT screenWidth, const UINT screenHeight);

public:
	UINT GetScreenWidth() const { return mScreenWidth; }
	UINT GetScreenHeight() const { return mScreenHeight; }
	Vector2 GetScreenSize() const  
	{  
		return Vector2(static_cast<float>(mScreenWidth), static_cast<float>(mScreenHeight)); 
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
	static void initialize(const HWND hwnd, const UINT screenWidth, const UINT screenHeight);

	void run();
	void update();
	void lateUpdate();
	void render();

private:
	HWND mHwnd;
	UINT mScreenWidth;
	UINT mScreenHeight;

	GraphicDeviceDX11* mGraphicDevice;
	RenderTargetRenderer* mRenderTargetRenderer;
};

#define gEngine Engine::GetInstance()
#define gGraphicDevice gEngine->GetGraphicDevice()
