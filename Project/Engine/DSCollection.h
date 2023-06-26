#pragma once
#include <d3d11.h>
#include <wrl/client.h>

enum class eDSType
{
	Less,
	Greater,
	NoWrite,
	None,
	End,
};

struct ID3D11Device;

class DSCollection
{
	friend class GraphicDeviceDX11;
private:
	DSCollection(ID3D11Device* const device);
	virtual ~DSCollection();
	DSCollection(const DSCollection&) = delete;
	DSCollection& operator=(const DSCollection&) = delete;

private:
	Microsoft::WRL::ComPtr<ID3D11DepthStencilState> mDStates[static_cast<UINT>(eDSType::End)];
};
