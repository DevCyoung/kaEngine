#include "pch.h"
#include "RSCollection.h"

RSCollection::RSCollection(ID3D11Device* const device)
{
	Assert(device, WCHAR_IS_NULLPTR);

	D3D11_RASTERIZER_DESC rasterizerDesc = {};
	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_BACK;
	device->CreateRasterizerState(&rasterizerDesc, mRStates[static_cast<UINT>(eRSType::SolidBack)].GetAddressOf());
	Assert(mRStates[static_cast<UINT>(eRSType::SolidBack)].Get(), WCHAR_IS_NULLPTR);

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_FRONT;
	device->CreateRasterizerState(&rasterizerDesc, mRStates[static_cast<UINT>(eRSType::SolidFront)].GetAddressOf());
	Assert(mRStates[static_cast<UINT>(eRSType::SolidFront)].Get(), WCHAR_IS_NULLPTR);

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_SOLID;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	device->CreateRasterizerState(&rasterizerDesc, mRStates[static_cast<UINT>(eRSType::SolidNone)].GetAddressOf());
	Assert(mRStates[static_cast<UINT>(eRSType::SolidNone)].Get(), WCHAR_IS_NULLPTR);

	rasterizerDesc.FillMode = D3D11_FILL_MODE::D3D11_FILL_WIREFRAME;
	rasterizerDesc.CullMode = D3D11_CULL_MODE::D3D11_CULL_NONE;
	device->CreateRasterizerState(&rasterizerDesc, mRStates[static_cast<UINT>(eRSType::WireframeNone)].GetAddressOf());
	Assert(mRStates[static_cast<UINT>(eRSType::WireframeNone)].Get(), WCHAR_IS_NULLPTR);

}

RSCollection::~RSCollection()
{
}
