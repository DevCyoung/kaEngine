#include "Time.h"
#include "Engine.h"

namespace engine
{
    double Time::mDeltaTime = 0.0l;
    double Time::mSecond = 0.0l;

    LARGE_INTEGER Time::mCpuFrequency = {};
    LARGE_INTEGER Time::mPrevFrequency = {};
    LARGE_INTEGER Time::mCurFrequency = {};

    Time::Time()
    {
    }

    Time::~Time()
    {
    }

    void Time::initiailize()
    {
        // CPU 고유 진동수 가져오기
        QueryPerformanceFrequency(&mCpuFrequency);

        // 프로그램이 처음 시작할때 진동수
        QueryPerformanceCounter(&mPrevFrequency);
    }

    void Time::update()
    {
        //갱신
        QueryPerformanceCounter(&mCurFrequency);

        const double differnceFrequency = static_cast<double>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

        mDeltaTime = differnceFrequency / static_cast<double>(mCpuFrequency.QuadPart);

        mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
    }

    void Time::render()
    {
        mSecond += mDeltaTime;

        if (mSecond > 1.0l)
        {
            const HWND hWnd = Engine::GetInst()->GetHwnd();

            wchar_t buffer[256] = {};
            const double fps = 1.0 / mDeltaTime;

            swprintf_s(buffer, 256, L"FPS : %lf", fps);
            SetWindowText(hWnd, buffer);

            mSecond = 0.0l;                                    
        }        
    }
}