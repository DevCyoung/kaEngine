#include "pch.h"
#include "ConstantBuffer.h"


	ConstantBuffer::ConstantBuffer(const eCBType CB_TYPE, const UINT BUFFER_SIZE, ID3D11Device* const device)
		: mType(CB_TYPE)
		, mDesc{}
		, mSize(BUFFER_SIZE)
		, mBuffer(nullptr)
	{
		Assert(device, WCHAR_IS_NULLPTR);
		Assert((mSize % 16) == 0, "data not al 16 byte!");		

		mDesc.ByteWidth = mSize;
		mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

		device->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf());
		Assert(mBuffer.Get(), WCHAR_IS_NULLPTR);		
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}
