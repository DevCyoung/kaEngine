#pragma once
#include "Engine.h"
#include "GraphicDeviceDx11.h"


namespace engine
{
    class Application
    {
        public:
        Application();
        virtual ~Application();

        void Initialize();

        void Run();
        void Update();
        void LateUpdate();
        void Render();

        void SetWindow(const HWND hwnd, const UINT width, const UINT height);
        UINT GetWidth() const { return mWidth; }
        UINT GetHeight() const { return mHeight; }
        HWND GetHwnd() const { return mHwnd; }

    private:        
        //smart pointer
        std::unique_ptr<engine::graphics::GraphicDeviceDX11> mGraphicDevice;

        HWND mHwnd;
        UINT mWidth;
        UINT mHeight;       

        bool mbInitialize = false;
    };
}
