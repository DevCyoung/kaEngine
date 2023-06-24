#include "pch.h"
#include "TimeManager.h"

namespace engine
{	
	TimeManager::TimeManager()
		: mDeltaTime(0.0f)
		, mSecond(0.0f)
		, mCpuFrequency{}
		, mPrevFrequency{}
		, mCurFrequency{}
	{
		QueryPerformanceFrequency(&mCpuFrequency);
		QueryPerformanceCounter(&mPrevFrequency);
	}

	TimeManager::~TimeManager()
	{
	}

	void TimeManager::update()
	{		
		QueryPerformanceCounter(&mCurFrequency);
		const float differnceFrequency = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
		mDeltaTime = differnceFrequency / static_cast<float>(mCpuFrequency.QuadPart);
		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void TimeManager::render(const HWND hWnd)
	{
		mSecond += mDeltaTime;

		if (1.0f < mSecond)
		{			
			wchar_t buffer[256] = {};
			const float fps = 1.0f / mDeltaTime;
			swprintf_s(buffer, 256, L"<SEO Egine> FPS : %f", fps);
			SetWindowText(hWnd, buffer);

			mSecond = 0.0f;
		}
	}
}
