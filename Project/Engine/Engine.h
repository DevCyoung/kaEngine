#pragma once

#include "Singleton.h"
#include <memory>
#include <assert.h>


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
    class Scene;
    class CBCollection;


    class Engine
    {    
        friend int APIENTRY ::wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance,
            _In_ LPWSTR    lpCmdLine, _In_ int       nCmdShow);
        SINGLETON_DECLARE(Engine);

        //SINGLETON(Engine);
    public:
        UINT GetScreenWidth() const { return mWidth; }
        UINT GetScreenHeight() const { return mHeight; }
        HWND GetHwnd() const { return mHwnd; }

        ID3D11Device* GetDevice() const;
        ID3D11DeviceContext* GetContext() const;
        graphics::GraphicDeviceDX11* GetGraphicDevice() const;
        CBCollection* GetCBCollection() { return mCBCollection.get(); }

    private:    
        static void initialize(const HWND hwnd, const UINT width, const UINT height);

        void setWindow(const HWND hwnd, const UINT width, const UINT height);
        void run();
        void update();
        void lateUpdate();        
        void render();    

    private: 
        std::unique_ptr<engine::graphics::GraphicDeviceDX11> mGraphicDevice;
        std::unique_ptr<CBCollection> mCBCollection;

        HWND mHwnd;
        UINT mWidth;
        UINT mHeight;        
        bool mbInitialize = false;

        //test
        //Scene* mTestCurrentScene;
    };    
}

#define gEngine engine::Engine::GetInstance()
#define gGraphicDevice gEngine->GetGraphicDevice()
#define gDevie gEngine->GetDevice()
#define gContext gEngine->GetContext()
#define gConstantBuffers gEngine->GetCBCollection()
