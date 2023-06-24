#include "pch.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"

namespace engine
{
	CBCollection::CBCollection(ID3D11Device* const device)
		: mConstantBuffers
		{
			ConstantBuffer(eCBType::Transform, sizeof(tTransform), device),						
		}
	{
	}

	CBCollection::~CBCollection()
	{
	}
}
