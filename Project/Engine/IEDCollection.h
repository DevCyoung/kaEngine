#pragma once

#include <d3d11.h>
#include <wrl/client.h>

enum class eIEDType
{
	Default,
	End,
};


class IEDCollection
{
	friend class GraphicDeviceDX11;

private:
	IEDCollection();
	virtual ~IEDCollection();
	IEDCollection(const IEDCollection&) = delete;
	IEDCollection& operator=(const IEDCollection&) = delete;

public:
	size_t GetIEDSize(const eIEDType IED_TYPE) const { return mIEDArrays[static_cast<UINT>(IED_TYPE)].size(); }
	const D3D11_INPUT_ELEMENT_DESC* GetData (const eIEDType IED_TYPE) const { return mIEDArrays[static_cast<UINT>(IED_TYPE)].data(); }


private:
	std::vector<D3D11_INPUT_ELEMENT_DESC> mIEDArrays[static_cast<UINT>(eIEDType::End)];
};

