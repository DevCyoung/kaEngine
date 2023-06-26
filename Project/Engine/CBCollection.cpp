#include "pch.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"


CBCollection::CBCollection(ID3D11Device* const device)
	: mConstantBuffers
	{
		ConstantBuffer(eCBType::Transform, sizeof(tTransform), device),
		ConstantBuffer(eCBType::ColorInfo, sizeof(tColorInfo), device)
	}
{
}

CBCollection::~CBCollection()
{
}
