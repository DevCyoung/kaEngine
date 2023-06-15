#include "pch.h"
#include "Mesh.h"

namespace engine
{
	Mesh::Mesh(const D3D11_BUFFER_DESC& pDesc,
		const D3D11_SUBRESOURCE_DATA* const pInitialData, ID3D11Device* const device)
		:mDesc(pDesc)
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

	HRESULT Mesh::Load(const std::wstring& path)
	{
		(void)path;
		return E_NOTIMPL;
	}
}