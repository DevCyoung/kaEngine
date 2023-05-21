#include "Application.h"

namespace engine
{
    Application::Application()
        : mGraphicDevice(nullptr)
        , mHwnd(nullptr)
        , mWidth(-1)
        , mHeight(-1)
        , mbInitialize(false)
    {
    }

    Application::~Application()
    {
    }

    void Application::Initialize()
    {        
    }

    void Application::Run()
    {        
    }

    void Application::Update()
    {
    }

    void Application::LateUpdate()
    {
    }

    void Application::Render()
    {
    }

    void Application::SetWindow(const HWND hwnd, const UINT width, const UINT height)
    {
        if (nullptr == mGraphicDevice)
        {
            mHwnd = hwnd;
            mWidth = width;
            mHeight = height;

            mGraphicDevice = std::make_unique<graphics::GraphicDeviceDx11>();
        }

        RECT wdScreen = { 0, 0, static_cast<LONG>(width), static_cast<LONG>(height) };
        AdjustWindowRect(&wdScreen, WS_OVERLAPPEDWINDOW, FALSE);
        SetWindowPos(mHwnd, nullptr /*HWND_TOP*/, 0, 0, wdScreen.right - wdScreen.left, wdScreen.bottom - wdScreen.top, 0/*SWP_NOMOVE | SWP_NOZORDER*/);
        ShowWindow(mHwnd, true);
        UpdateWindow(mHwnd);
    }

  
}   