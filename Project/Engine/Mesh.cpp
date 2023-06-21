#include "pch.h"
#include "Mesh.h"

namespace engine
{
	Mesh::Mesh(const D3D11_BUFFER_DESC& pDesc,
		const D3D11_SUBRESOURCE_DATA* const pInitialData,
		const UINT vertexSize,
		const UINT vertexCount,
		ID3D11Device* const device)
		: mDesc(pDesc)
		, mVertexSize(vertexSize)
		, mVertexCount(vertexCount)
	{
		assert(mDesc.BindFlags == D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER);

		if (FAILED(device->CreateBuffer(&mDesc, pInitialData, mBuffer.GetAddressOf())))
		{
			assert(false);
		}
	}

	Mesh::~Mesh()
	{
	}

	UINT Mesh::GetMeshSize() const
	{
		return mDesc.ByteWidth;
	}

	UINT Mesh::GetVertexSize() const
	{
		return mVertexSize;
	}

	UINT Mesh::GetVertexCount() const
	{
		return mVertexCount;
	}

	HRESULT Mesh::Load(const std::wstring& path)
	{
		assert(false);

		(void)path;
		return E_NOTIMPL;
	}
}