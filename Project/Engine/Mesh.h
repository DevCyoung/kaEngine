#pragma once
#include <wrl.h>
#include <d3d11.h>
#include "Resource.h"

namespace graphics
{
	class GraphicDeviceDX11;
}

namespace engine
{
	class Mesh : public Resource
	{
		friend class graphics::GraphicDeviceDX11;
		friend class ResourceManager;

	private:		
		Mesh(const D3D11_BUFFER_DESC& pDesc, const D3D11_SUBRESOURCE_DATA* const pInitialData,
			const UINT vertexSize, const UINT vertexCount, ID3D11Device* const device);		
		Mesh(const Mesh&) = delete;
		Mesh& operator=(const Mesh&) = delete;

	public:
		virtual ~Mesh();
		UINT GetMeshSize() const;
		UINT GetVertexSize() const;
		UINT GetVertexCount() const;
		virtual HRESULT Load(const std::wstring& path) override;

	private:
		D3D11_BUFFER_DESC mDesc;
		UINT mVertexSize;
		UINT mVertexCount;

		Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
	};
}