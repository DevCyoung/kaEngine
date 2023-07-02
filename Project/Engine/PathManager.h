#pragma once
#include "Singleton.h"

class PathManager
{
	friend class Engine;
	SINGLETON_DECLARE(PathManager);

public:
	const wchar_t* GetResourcePath() const { return mResourcePath; }

private:
	wchar_t	mResourcePath[256];
};

#define gPathManager PathManager::GetInstance()
