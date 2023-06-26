#include "pch.h"
#include "Mesh.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"


	Mesh::Mesh(const D3D11_BUFFER_DESC& pDesc,
		const D3D11_SUBRESOURCE_DATA* const pInitialData,
		const UINT vertexSize,
		const UINT vertexCount)
		: mDesc(pDesc)
		, mVertexSize(vertexSize)
		, mVertexCount(vertexCount)
	{		
		Assert(mDesc.BindFlags == D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER, WCHAR_IS_INVALID_TYPE);

		if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateBuffer(&mDesc, pInitialData, mBuffer.GetAddressOf())))
		{
			Assert(false, L"failed to create buffer");
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
		Assert(false, L"");

		(void)path;
		return E_NOTIMPL;
	}
