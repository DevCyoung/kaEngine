#include "pch.h"
#include "TimeManager.h"
#include "MessageManager.h"

TimeManager::TimeManager()
	: mDeltaTime(0.0f)
	, mGlobalTime(0.0f)
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
	const float DIFERENCE_FREQUENCY = static_cast<float>(mCurFrequency.QuadPart - mPrevFrequency.QuadPart);
	mDeltaTime = DIFERENCE_FREQUENCY / static_cast<float>(mCpuFrequency.QuadPart);
	mGlobalTime += mDeltaTime;
	mPrevFrequency.QuadPart = mCurFrequency.QuadPart;

	if (MessageManager::GetInstance()->IsSendMessage())
	{
		constexpr UINT WSTR_LEN = 256;
		const float FPS = 1.0f / mDeltaTime;		
		wchar_t buffer[WSTR_LEN] = { 0, };
		swprintf_s(buffer, WSTR_LEN, L"<FPS : %.f>", FPS);

		MessageManager::GetInstance()->AddMessage(buffer);
	}

}

void TimeManager::StartTime(LARGE_INTEGER* const starTime)
{
	QueryPerformanceCounter(starTime);
}

float TimeManager::EndTime(LARGE_INTEGER* const starTime)
{
	LARGE_INTEGER endTime;

	QueryPerformanceCounter(&endTime);

	const float DIFERENCE_FREQUENCY = static_cast<float>(endTime.QuadPart - starTime->QuadPart);
	return DIFERENCE_FREQUENCY / static_cast<float>(mCpuFrequency.QuadPart);
}
