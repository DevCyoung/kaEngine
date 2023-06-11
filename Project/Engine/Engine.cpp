#include "Engine.h"
#include "GraphicDeviceDx11.h"

#include "Input.h"
#include "Time.h"

#include "Scene.h"
#include "Shader.h"


namespace engine
{
    Engine::Engine()
        : mGraphicDevice(nullptr)
        , mHwnd(nullptr)
        , mWidth(static_cast<UINT>(-1))
        , mHeight(static_cast<UINT>(-1))
        , mbInitialize(false)
        , mCurrentScene(nullptr)
    {
    }

    Engine::~Engine()
    {
        if (nullptr != mCurrentScene)
        {
            delete mCurrentScene;
        }
    }

    ID3D11Device* Engine::GetDevice() const
    {
        return mGraphicDevice->mDevice.Get();
    }

    ID3D11DeviceContext* Engine::GetContext() const
    {
        return mGraphicDevice->mContext.Get();
    }

    void Engine::initialize()
    {       
        Time::initiailize();  

        Input::initialize();

        mCurrentScene = new Scene();        
    }

    void Engine::run()
    {        
        update();

        lateUpdate();

        render();
    }

    void Engine::update()
    {
        Time::update();

        Input::update();

        if (nullptr != mCurrentScene)
        {
            mCurrentScene->update();
        }        
    }

    void Engine::lateUpdate()
    {
        if (nullptr != mCurrentScene)
        {
            mCurrentScene->lateUpdate();
        }
    }

    void Engine::render()
    {        
        Time::render();

        mGraphicDevice->clearRenderTarget();


        if (nullptr != mCurrentScene)
        {
            mCurrentScene->render();
        }
        

        mGraphicDevice->present();
    }

    void Engine::setWindow(const HWND hwnd, const UINT width, const UINT height)
    {
        if (nullptr == mGraphicDevice)
        {
            mHwnd = hwnd;
            mWidth = width;
            mHeight = height;

            mGraphicDevice = std::make_unique<graphics::GraphicDeviceDX11>();
        }

        RECT wdScreen = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
        AdjustWindowRect(&wdScreen, WS_OVERLAPPEDWINDOW, FALSE);
        SetWindowPos(mHwnd,
            nullptr /*HWND_TOP*/, 0, 0,
            wdScreen.right - wdScreen.left,
            wdScreen.bottom - wdScreen.top, 0/*SWP_NOMOVE | SWP_NOZORDER*/);

        ShowWindow(mHwnd, true);
        UpdateWindow(mHwnd);
    }
}