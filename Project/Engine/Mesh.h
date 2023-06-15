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
		friend class MeshCollection;

	private:		
		Mesh(const D3D11_BUFFER_DESC& pDesc, const D3D11_SUBRESOURCE_DATA* const pInitialData,
			ID3D11Device* const device);		
		Mesh(const Mesh& other) = delete;
		Mesh& operator =(const Mesh& other) = delete;
	public:
		virtual ~Mesh();

		virtual HRESULT Load(const std::wstring& path) override;

	private:
		D3D11_BUFFER_DESC mDesc;
		Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
	};
}