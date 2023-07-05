#include "pch.h"
#include "CBCollection.h"
#include "StructConstantBuffer.h"


CBCollection::CBCollection(ID3D11Device* const device)
	: mConstantBuffers
	{
		ConstantBuffer(eCBType::Transform, sizeof(tCBTransform), device),
		ConstantBuffer(eCBType::ColorInfo, sizeof(tCBColorInfo), device),
		ConstantBuffer(eCBType::GridInfo, sizeof(tCBGridInfo), device),
	}
{
}

CBCollection::~CBCollection()
{
}
		