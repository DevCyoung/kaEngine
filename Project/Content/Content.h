#pragma once
#include <Engine/Singleton.h>

namespace content
{
	class Content
	{
		friend int APIENTRY::wWinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance,
			LPWSTR lpCmdLine, int nCmdShow);
		SINGLETON_DECLARE(Content);
	};
}
