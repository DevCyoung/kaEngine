#include "Time.h"

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

    void Time::Initiailize()
    {
        // CPU 고유 진동수 가져오기
        QueryPerformanceFrequency(&mCpuFrequency);

        // 프로그램이 처음 시작할때 진동수
        QueryPerformanceCounter(&mPrevFrequency);
    }

    void Time::Update()
    {
        //갱신
        QueryPerformanceCounter(&mCurFrequency);

        const double differnceFrequency = static_cast<double>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

        mDeltaTime = differnceFrequency / mCpuFrequency.QuadPart;

        mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
    }

    void Time::Render(const HDC hdc)
    {
        mSecond += mDeltaTime;

        if (mSecond > 1.0l)
        {
            //const HWND hWnd = application.GetHwnd();

            wchar_t buffer[256] = {};
            double fps = 1.0l / mDeltaTime;
            //swprintf_s(hWnd, buffer)
            
        }
    }
}