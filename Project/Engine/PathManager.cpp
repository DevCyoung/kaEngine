#include "pch.h"
#include "PathManager.h"

PathManager::PathManager()
	: mResourcePath{ 0, }
{
	GetCurrentDirectory(256, mResourcePath);

	// 상위폴더로 감
	const int pathLen = static_cast<int>(wcslen(mResourcePath));

	for (int i = pathLen - 1; i >= 0; --i)
	{
		if (L'\\' == mResourcePath[i])
		{
			mResourcePath[i] = '\0';
			break;
		}
	}

	wcscat_s(mResourcePath, L"\\bin\\Resources");
}

PathManager::~PathManager()
{
}
