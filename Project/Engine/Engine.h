#pragma once
#include <memory>
#include <assert.h>
#include "Singleton.h"
#include "DefineMacro.h"

namespace engine
{  
    namespace graphics
    {
        class GraphicDeviceDX11;
    }
        
    class Engine
    {    
        friend int APIENTRY ::wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
            LPWSTR lpCmdLine, int nCmdShow);       
        SINGLETON_DECLARE(Engine);

    private:
        Engine(const HWND hWnd, const UINT screenWidth, const UINT screenHeight);

    public:
        UINT GetScreenWidth() const { return mScreenWidth; }
        UINT GetScreenHeight() const { return mScreenHeight; }
        HWND GetHwnd() const { Assert(mHwnd, WCHAR_IS_NULLPTR); return mHwnd; }
        graphics::GraphicDeviceDX11* GetGraphicDevice() const { return mGraphicDevice; }

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
        graphics::GraphicDeviceDX11* mGraphicDevice;
    };    
}

#define gEngine engine::Engine::GetInstance()
#define gGraphicDevice gEngine->GetGraphicDevice()
