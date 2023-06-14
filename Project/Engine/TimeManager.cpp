#include "pch.h"
#include "TimeManager.h"
#include "Engine.h"

namespace engine
{

	TimeManager::TimeManager()
		: mDeltaTime(0.0l)
		, mSecond(0.0l)
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

		// CPU ���� ������ ��������
		QueryPerformanceFrequency(&(sInstance->mCpuFrequency));

		// ���α׷��� ó�� �����Ҷ� ������
		QueryPerformanceCounter(&(sInstance->mPrevFrequency));

	}


	void TimeManager::update()
	{
		//����
		QueryPerformanceCounter(&mCurFrequency);

		const float differnceFrequency = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);

		mDeltaTime = differnceFrequency / static_cast<float>(mCpuFrequency.QuadPart);

		mPrevFrequency.QuadPart = mCurFrequency.QuadPart;
	}

	void TimeManager::render()
	{
		mSecond += mDeltaTime;

		if (mSecond > 1.0f)
		{
			const HWND hWnd = gEngine->GetHwnd();

			wchar_t buffer[256] = {};
			const float fps = 1.0f / mDeltaTime;

			swprintf_s(buffer, 256, L"FPS : %f", fps);
			SetWindowText(hWnd, buffer);

			mSecond = 0.0l;
		}
	}
}