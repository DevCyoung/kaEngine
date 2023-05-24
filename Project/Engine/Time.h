#pragma once
#include "Engine.h"

namespace engine
{
    class Time
    {
	private:
		friend class Application;

	private:
		Time();
        virtual ~Time();

	private:
		static void Initiailize();	
		static void Update();	
		static void Render(const HDC hdc);

	public:
		static double DeltaTime() { return mDeltaTime; }

	private:
		static double mDeltaTime;
		static double mSecond;
		static LARGE_INTEGER mCpuFrequency;
		static LARGE_INTEGER mPrevFrequency;
		static LARGE_INTEGER mCurFrequency;
    };
}