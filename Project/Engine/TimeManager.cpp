#include "pch.h"
#include "TimeManager.h"
#include "MessageManager.h"

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

	const float fps = 1.0f / mDeltaTime;

	constexpr UINT bufferSize = 256;
	wchar_t buffer[bufferSize] = { 0, };
	swprintf_s(buffer, bufferSize, L"<FPS : %.2f>", fps);

	MessageManager::GetInstance()->AddMessage(buffer);
}
