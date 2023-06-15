#include "pch.h"
#include "CBCollection.h"

namespace engine
{
	CBCollection::CBCollection(ID3D11Device* const device)
		: mConstantBuffers
		{
			ConstantBuffer(eCBType::Transform, 16, device),
			ConstantBuffer(eCBType::ParticleInfo, 16, device),
			ConstantBuffer(eCBType::Dummy, 16, device),
		}
	{
	}

	CBCollection::~CBCollection()
	{
	}
}