#pragma once
#include <wrl.h>
#include <d3d11.h>

enum class eCBType
{
	Transform,
	ColorInfo,
	DebugInfo, // 2
	End,
};

class ConstantBuffer
{
	friend class CBCollection;
	friend class GraphicDeviceDX11;

private:
	ConstantBuffer(const eCBType CB_TYPE, const UINT BUFFER_SIZE, ID3D11Device* const device);
	virtual ~ConstantBuffer();
	ConstantBuffer(const ConstantBuffer&) = delete;
	ConstantBuffer& operator=(const ConstantBuffer&) = delete;

private:
	eCBType mType;
	D3D11_BUFFER_DESC mDesc;
	UINT mSize;
	Microsoft::WRL::ComPtr<ID3D11Buffer> mBuffer;
};
