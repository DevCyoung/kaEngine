#pragma once

#include "ConstantBuffer.h"
#include "Singleton.h"

namespace engine
{
	class ConstantBufferManager
	{
		friend class Engine;
		SINGLETON_DECLARE(ConstantBufferManager);

	public:
		ConstantBuffer& GetCBTransform() { return mCBTransform; }

	private:
		ConstantBuffer mCBTransform;

	};
}
