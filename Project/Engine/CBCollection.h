#pragma once
#include "ConstantBuffer.h"

struct ID3D11Device;

namespace engine
{
	namespace graphics
	{
		class GraphicDeviceDX11;
	}

	class CBCollection
	{
		friend class graphics::GraphicDeviceDX11;
	private:
		CBCollection(ID3D11Device* device);
		virtual ~CBCollection();
		CBCollection(const CBCollection&) = delete;
		CBCollection& operator=(const CBCollection&) = delete;

		ConstantBuffer& GetConstantBuffer(const eCBType type)
		{
			return mConstantBuffers[static_cast<UINT>(type)];
		}

	private:
		ConstantBuffer mConstantBuffers[static_cast<UINT>(eCBType::End)];
	};
}