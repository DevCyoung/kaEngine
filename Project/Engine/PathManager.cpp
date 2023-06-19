#include "pch.h"
#include "PathManager.h"

namespace engine
{
	PathManager::PathManager()
		: mResourcePath{0,}
	{

	}

	PathManager::~PathManager()
	{

	}

	void PathManager::initialize()
	{
		assert(!sInstance);
		sInstance = new PathManager();

		GetCurrentDirectory(256, sInstance->mResourcePath);

		// 상위폴더로 감
		int iLen = static_cast<int>(wcslen(sInstance->mResourcePath));

		for (int i = iLen - 1; i >= 0; --i)
		{
			if (L'\\' == sInstance->mResourcePath[i])
			{
				sInstance->mResourcePath[i] = 0;
				break;
			}
		}
		
		wcscat_s(sInstance->mResourcePath, L"\\bin\\Resources");
	}

}