#include "pch.h"
#include "DSCollection.h"

DSCollection::DSCollection(ID3D11Device* const device)
{
	Assert(device, WCHAR_IS_NULLPTR);
	D3D11_DEPTH_STENCIL_DESC depthStencilDesc = {};

	//less
	depthStencilDesc = {};
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.StencilEnable = false;
	device->CreateDepthStencilState(&depthStencilDesc
		, mDStates[(UINT)eDSType::Less].GetAddressOf());
	Assert(mDStates[static_cast<UINT>(eDSType::Less)].Get(), WCHAR_IS_NULLPTR);

	//less Equal
	depthStencilDesc = {};
	depthStencilDesc.DepthEnable = true;	
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS_EQUAL;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.StencilEnable = false;
	device->CreateDepthStencilState(&depthStencilDesc
		, mDStates[(UINT)eDSType::LessEqual].GetAddressOf());
	Assert(mDStates[static_cast<UINT>(eDSType::LessEqual)].Get(), WCHAR_IS_NULLPTR);

	//Greater
	depthStencilDesc = {};
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_GREATER;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ALL;
	depthStencilDesc.StencilEnable = false;
	device->CreateDepthStencilState(&depthStencilDesc
		, mDStates[(UINT)eDSType::Greater].GetAddressOf());
	Assert(mDStates[static_cast<UINT>(eDSType::Greater)].Get(), WCHAR_IS_NULLPTR);

	//No Write
	depthStencilDesc = {};
	depthStencilDesc.DepthEnable = true;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.StencilEnable = false;
	device->CreateDepthStencilState(&depthStencilDesc
		, mDStates[(UINT)eDSType::NoWrite].GetAddressOf());
	Assert(mDStates[static_cast<UINT>(eDSType::NoWrite)].Get(), WCHAR_IS_NULLPTR);

	//None
	depthStencilDesc = {};
	depthStencilDesc.DepthEnable = false;
	depthStencilDesc.DepthFunc = D3D11_COMPARISON_FUNC::D3D11_COMPARISON_LESS;
	depthStencilDesc.DepthWriteMask = D3D11_DEPTH_WRITE_MASK_ZERO;
	depthStencilDesc.StencilEnable = false;
	device->CreateDepthStencilState(&depthStencilDesc
		, mDStates[(UINT)eDSType::None].GetAddressOf());
	Assert(mDStates[static_cast<UINT>(eDSType::None)].Get(), WCHAR_IS_NULLPTR);
}

DSCollection::~DSCollection()
{
}
