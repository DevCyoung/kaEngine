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
	}

	TimeManager::~TimeManager()
	{
	}

	void TimeManager::initialize()
	{
		assert(!sInstance);
		sInstance = new TimeManager();

		// CPU 고유 진동수 가져오기
		QueryPerformanceFrequency(&(sInstance->mCpuFrequency));

		// 프로그램이 처음 시작할때 진동수
		QueryPerformanceCounter(&(sInstance->mPrevFrequency));

	}

	void TimeManager::update()
	{
		//갱신
		QueryPerformanceCounter(&mCurFrequency);

		const float differnceFrequency = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		mDeltaTime = differnceFrequency / static_cast<float>(mCpuFrequency.QuadPart);

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void TimeManager::render(const HWND hWnd)
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{			
			wchar_t buffer[256] = {};
			const float fps = 1.0f / mDeltaTime;

			swprintf_s(buffer, 256, L"<SEO Egine> FPS : %f", fps);
			SetWindowText(hWnd, buffer);

			mSecond = 0.0l;
		}
	}
}
