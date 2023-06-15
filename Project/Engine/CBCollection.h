#pragma once
#include "ConstantBuffer.h"

struct ID3D11Device;

namespace graphics
{
	class GraphicDeviceDX11;	
}

namespace engine
{
	class CBCollection
	{
		friend class graphics::GraphicDeviceDX11;

	private:
		CBCollection(ID3D11Device* device);
		CBCollection(const CBCollection& other) = delete;
		CBCollection& operator =(const CBCollection& other) = delete;				
		virtual ~CBCollection();
		ConstantBuffer& GetConstantBuffer(const eCBType type)
		{
			return mConstantBuffers[static_cast<UINT>(type)];
		}

	private:
		ConstantBuffer mConstantBuffers[static_cast<UINT>(eCBType::End)];
	};
}