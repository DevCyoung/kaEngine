#pragma once

#include "EngineIncludes.h"
#include "Singleton.h"


namespace engine::graphics
{
    class GraphicDeviceDX11;
}

namespace engine
{
    class Engine
    {    
        SINGLETON(Engine);
        friend int APIENTRY ::wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
            _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow);

    private:        
        void Initialize();                   
        void SetWindow(const HWND hwnd, const UINT width, const UINT height);

        void Run();

        void Update();
        void LateUpdate();        
        void Render();


    public:        
        UINT GetScreenWidth() const { return mWidth; }
        UINT GetScreenHeight() const { return mHeight; }
        HWND GetHwnd() const { return mHwnd; }                   

    private:        
        std::unique_ptr<engine::graphics::GraphicDeviceDX11> mGraphicDevice;

        HWND mHwnd;
        UINT mWidth;
        UINT mHeight;       

        bool mbInitialize = false;
    };    
}