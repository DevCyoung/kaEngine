#include "pch.h"
#include "ConstantBufferManager.h"

namespace engine
{
	ConstantBufferManager::ConstantBufferManager()
		: mCBTransform(eCBType::Transform, 16)
	{				
	}

	ConstantBufferManager::~ConstantBufferManager()
	{
	}

	
	void ConstantBufferManager::initialize()
	{
		assert(!sInstance);
		sInstance = new ConstantBufferManager();
	}
}
