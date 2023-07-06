#include "pch.h"
#include "Mesh.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

Mesh::Mesh(
	const void* const VERTEX_DATA_ARRAY,
	const size_t VERTEX_COUNT,
	const size_t VERTEX_DATA_SIZE,
	const void* const INDEX_DATA_ARRAY,
	const size_t INDEX_COUNT,
	const size_t INDEX_DATA_SIZE)
	: mVertexBuffer(nullptr)
	, mVertexCount(VERTEX_COUNT)
	, mVertexSize(VERTEX_DATA_SIZE)
	, mVertexDesc{}
	, mIndexBuffer(nullptr)
	, mIndexCount(INDEX_COUNT)
	, mIndexSize(INDEX_DATA_SIZE)
	, mIdexDesc{}
{

	//Create Vertex Buffer
	mVertexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
	mVertexDesc.CPUAccessFlags = 0;
	mVertexDesc.Usage = D3D11_USAGE_DEFAULT;
	mVertexDesc.ByteWidth = static_cast<UINT>(mVertexSize * mVertexCount);

	D3D11_SUBRESOURCE_DATA tVertexSub = {};
	tVertexSub.pSysMem = VERTEX_DATA_ARRAY;

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateBuffer(&mVertexDesc, &tVertexSub, mVertexBuffer.GetAddressOf())))
	{
		Assert(false, L"failed to create vertex buffer");
	}

	//Create Index Buffer
	mIdexDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_INDEX_BUFFER;
	mIdexDesc.CPUAccessFlags = 0;
	mIdexDesc.Usage = D3D11_USAGE_DEFAULT;
	mIdexDesc.ByteWidth = static_cast<UINT>(mIndexSize * mIndexCount);

	D3D11_SUBRESOURCE_DATA tIndexSub = {};
	tIndexSub.pSysMem = INDEX_DATA_ARRAY;

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateBuffer(&mIdexDesc, &tIndexSub, mIndexBuffer.GetAddressOf())))
	{
		Assert(false, L"failed to create index buffer");
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
