#pragma once
#include "EngineIncludes.h"
#include "Singleton.h"

namespace engine
{
    namespace graphics
    {
        class GraphicDeviceDX11;
    }
}

struct ID3D11Device;
struct ID3D11DeviceContext;

namespace engine
{
    class Engine
    {    
        SINGLETON(Engine);
        friend int APIENTRY ::wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
            _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow);

    private:        
        void initialize();                   
        void setWindow(const HWND hwnd, const UINT width, const UINT height);
        void run();
        void update();
        void lateUpdate();        
        void render();


    public:        
        UINT GetScreenWidth() const { return mWidth; }
        UINT GetScreenHeight() const { return mHeight; }
        HWND GetHwnd() const { return mHwnd; }

        inline ID3D11Device* GetDevice() const;
        inline ID3D11DeviceContext* GetContext() const;

    private: 
        std::unique_ptr<engine::graphics::GraphicDeviceDX11> mGraphicDevice;

        HWND mHwnd;
        UINT mWidth;
        UINT mHeight;       

        bool mbInitialize = false;
    };    
}