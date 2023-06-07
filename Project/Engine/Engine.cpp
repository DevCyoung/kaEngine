#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "Input.h"
#include "Time.h"

namespace engine
{
    Engine::Engine()
        : mGraphicDevice(nullptr)
        , mHwnd(nullptr)
        , mWidth(static_cast<UINT>(-1))
        , mHeight(static_cast<UINT>(-1))
        , mbInitialize(false)
    {
    }

    Engine::~Engine()
    {
    }

    void Engine::initialize()
    {
        Time::Initiailize();  
        Input::Initialize();
    }

    void Engine::run()
    {        
        update();
        lateUpdate();
        render();
    }

    void Engine::update()
    {
        (void)mGraphicDevice->mDevice;


        Time::Update();
        Input::Update();        
    }

    void Engine::lateUpdate()
    {
    }

    void Engine::render()
    {        
        mGraphicDevice->Draw();
        Time::Render();
    }

    inline ID3D11Device* Engine::GetDevice() const
    {
        return mGraphicDevice->mDevice.Get();
    }

    inline ID3D11DeviceContext* Engine::GetContext() const 
    {
        Engine::GetInst()->GetDevice();

        return mGraphicDevice->mContext.Get();
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