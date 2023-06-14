#pragma once
#include "ConstantBuffer.h"

namespace engine
{
	class CBCollection
	{
	public:
		CBCollection();
		virtual ~CBCollection();

		void Initialize();

	public:
		ConstantBuffer& GetCBTransform() { return transform; }

	private:
		ConstantBuffer transform;	
	};
}
