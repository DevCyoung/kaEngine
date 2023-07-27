#include "pch.h"
#include "SBCollection.h"
#include "StructConstantBuffer.h"

SBCollection::SBCollection(ID3D11Device* const device)
	: mStructuredBuffers{}
{
	{
		const eSBType SBType = eSBType::Light2D;
		const UINT slot = static_cast<UINT>(SBType);
		mStructuredBuffers[slot] = 
			new StructuredBuffer(SBType, eSRVTpye::Light2DBuffer, sizeof(tLightInfo), 1, nullptr, device);
	}	
}

SBCollection::~SBCollection()
{
	for (UINT i = 0; i < static_cast<UINT>(eSBType::End); ++i)
	{
		SAFE_DELETE_POINTER(mStructuredBuffers[i]);
	}
}

void SBCollection::ReSizeStructuredBuffer(const eSBType SBType,
	const eSRVTpye SRVType,
	const UINT dataSize,
	const UINT stride,
	const void* const dataOrNull, 
	ID3D11Device* const device)
{	
	const UINT slot = static_cast<UINT>(SBType);

	SAFE_DELETE_POINTER(mStructuredBuffers[slot]);

	mStructuredBuffers[slot] = new StructuredBuffer(SBType, SRVType, dataSize, stride, dataOrNull, device);
}
