#pragma once
#include <memory>
#include <assert.h>

#include "Singleton.h"



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

    public:
        UINT GetScreenWidth() const { return mScreenWidth; }
        UINT GetScreenHeight() const { return mScreenHeight; }
        HWND GetHwnd() const { return mHwnd; }        
        graphics::GraphicDeviceDX11* GetGraphicDevice() const { return mGraphicDevice.get(); }

    private:    
        static void initialize(const HWND hwnd, const UINT width, const UINT height);
        void setWindow(const HWND hwnd, const UINT width, const UINT height);
        void run();
        void update();
        void lateUpdate();        
        void render();

    private: 
        std::unique_ptr<engine::graphics::GraphicDeviceDX11> mGraphicDevice;
        HWND mHwnd;
        UINT mScreenWidth;
        UINT mScreenHeight;        
        
    };    
}

#define gEngine engine::Engine::GetInstance()
#define gGraphicDevice gEngine->GetGraphicDevice()