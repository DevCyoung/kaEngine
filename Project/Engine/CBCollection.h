#pragma once
#include "ConstantBuffer.h"

struct ID3D11Device;
class GraphicDeviceDX11;

class CBCollection
{
	friend class GraphicDeviceDX11;
private:
	CBCollection(ID3D11Device* const device);
	virtual ~CBCollection();
	CBCollection(const CBCollection&) = delete;
	CBCollection& operator=(const CBCollection&) = delete;

	ConstantBuffer& GetConstantBuffer(const eCBType CB_TYPE) { return mConstantBuffers[static_cast<UINT>(CB_TYPE)]; }

private:
	ConstantBuffer mConstantBuffers[static_cast<UINT>(eCBType::End)];
};
