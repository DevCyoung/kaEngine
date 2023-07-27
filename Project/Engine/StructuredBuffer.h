#pragma once
#include <d3d11.h>
#include <wrl/client.h>
#include "EnumSRV.h"

//enum class SB_TYPE
//{
//	READ_ONLY,
//	READ_WRITE,
//};

enum class eSBType
{
	Light2D,
	End,
};


class StructuredBuffer
{
	friend class GraphicDeviceDX11;
public:
	StructuredBuffer(const eSBType CBType,
		const eSRVTpye SRVType,
		const UINT dataSize,
		const UINT stride,
		const void* const dataOrNull, ID3D11Device* const device);

	virtual ~StructuredBuffer();
	StructuredBuffer(const StructuredBuffer&) = delete;
	StructuredBuffer& operator=(const StructuredBuffer&) = delete;

	//void Create(const UINT dataSize, const UINT stride, void* const dataOrNull, ID3D11Device* const device);

	//bool Create(UINT size, UINT stride, eSRVType type);
	//void SetData(void* data, UINT stride);
	////void Bind(eShaderStage stage, UINT slot);
	//
	//UINT GetSize() { return mSize; }
	//UINT GetStride() { return mStride; }

	//void Resize(UINT size, UINT stride, eSRVType type);

private:
	//eSRVType mType;

	Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
	D3D11_BUFFER_DESC mDesc;
	eSBType mType;
	eSRVTpye mSRVType;
	UINT mSize;
	UINT mStride;
};
