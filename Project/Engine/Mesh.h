#pragma once
#include <wrl.h>
#include <d3d11.h>
#include "Resource.h"

class Mesh : public Resource
{
	friend class GraphicDeviceDX11;
public:
	Mesh(
		const void* const vertexData,
		const size_t vertexCount,
		const size_t vertexSize,
		const void* const indexData,
		const size_t indexCount,
		const size_t indexSize);

	Mesh(const Mesh&) = delete;
	Mesh& operator=(const Mesh&) = delete;

public:
	virtual ~Mesh();	
	UINT GetVertexCount() const { return static_cast<UINT>(mVertexCount); }
	UINT GetIndexCount()  const { return static_cast<UINT>(mIndexCount); }
	virtual HRESULT Load(const std::wstring& path) override;

private:
	Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
	size_t mVertexCount;
	size_t mVertexSize;
	D3D11_BUFFER_DESC mVertexDesc;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mIndexBuffer;
	size_t mIndexCount;
	size_t mIndexSize;
	D3D11_BUFFER_DESC mIdexDesc;
};
