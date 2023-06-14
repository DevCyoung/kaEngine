#include "pch.h"
#include "ConstantBuffer.h"
#include "Engine.h"

namespace engine
{
	ConstantBuffer::ConstantBuffer(const eCBType type, const UINT size)
		: mType(type)
		, mDesc{}
		, mBuffer(nullptr)
	{
		assert((size % 16) == 0);

		mDesc.ByteWidth = size;
		mDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_CONSTANT_BUFFER;
		mDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;
		mDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;

		gDevie->CreateBuffer(&mDesc, nullptr, mBuffer.GetAddressOf());
		assert(mBuffer.Get());
	}

	ConstantBuffer::~ConstantBuffer()
	{
	}

	void ConstantBuffer::SetData(const void* const data)
	{
		assert(data);

		D3D11_MAPPED_SUBRESOURCE subResource = {};		
		gContext->Map(mBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		{
			memcpy_s(subResource.pData, mDesc.ByteWidth, data, mDesc.ByteWidth);
		}
		gContext->Unmap(mBuffer.Get(), 0);
	}

	/*void ConstantBuffer::Bind(const eShaderStage stage) const
	{
		const UINT startSlot = static_cast<UINT>(mType);

		switch (stage)
		{
		case eShaderStage::VS:
			Engine::GetInst()->GetContext()->VSSetConstantBuffers(startSlot, 1, mBuffer.GetAddressOf());
			break;
		case eShaderStage::HS:
			Engine::GetInst()->GetContext()->HSSetConstantBuffers(startSlot, 1, mBuffer.GetAddressOf());
			break;
		case eShaderStage::DS:
			Engine::GetInst()->GetContext()->DSSetConstantBuffers(startSlot, 1, mBuffer.GetAddressOf());
			break;
		case eShaderStage::GS:
			Engine::GetInst()->GetContext()->GSSetConstantBuffers(startSlot, 1, mBuffer.GetAddressOf());
			break;
		case eShaderStage::PS:
			Engine::GetInst()->GetContext()->PSSetConstantBuffers(startSlot, 1, mBuffer.GetAddressOf());
			break;
		case eShaderStage::CS:
			Engine::GetInst()->GetContext()->CSSetConstantBuffers(startSlot, 1, mBuffer.GetAddressOf());
			break;		
		default:
			assert(nullptr);
			break;
		}
	}*/
}