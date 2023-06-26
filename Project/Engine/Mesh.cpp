#include "pch.h"
#include "Mesh.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

Mesh::Mesh(
	const void* const vertexData,
	const size_t vertexCount,
	const size_t vertexSize,
	const void* const indexData,
	const size_t indexCount,
	const size_t indexSize)
	: mVertexBuffer(nullptr)
	, mVertexCount(vertexCount)
	, mVertexSize(vertexSize)
	, mVertexDesc{}
	, mIndexBuffer(nullptr)
	, mIndexCount(indexCount)
	, mIndexSize(indexSize)
	, mIdexDesc{}
{

	{
		//Create Vertex Buffer
		mVertexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
		mVertexDesc.CPUAccessFlags = 0;
		mVertexDesc.Usage = D3D11_USAGE_DEFAULT;
		mVertexDesc.ByteWidth = static_cast<UINT>(mVertexSize * mVertexCount);
		D3D11_SUBRESOURCE_DATA tSub = {};
		tSub.pSysMem = vertexData;
		if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateBuffer(&mVertexDesc, &tSub, mVertexBuffer.GetAddressOf())))
		{
			Assert(false, L"failed to create vertex buffer");
		}
	}

	{
		//Create Index Buffer
		mIdexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
		mIdexDesc.CPUAccessFlags = 0;
		mIdexDesc.Usage = D3D11_USAGE_DEFAULT;
		mIdexDesc.ByteWidth = static_cast<UINT>(mIndexSize * mIndexCount);
		D3D11_SUBRESOURCE_DATA tSub = {};
		tSub.pSysMem = indexData;
		if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateBuffer(&mIdexDesc, &tSub, mIndexBuffer.GetAddressOf())))
		{
			Assert(false, L"failed to create index buffer");
		}
	}
}

Mesh::~Mesh()
{
}

HRESULT Mesh::Load(const std::wstring& path)
{
	Assert(false, L"");

	(void)path;
	return E_NOTIMPL;
}
