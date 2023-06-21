#include "pch.h"
#include "GraphicDeviceDX11.h"
#include "StructVertex.h"
#include "CBCollection.h"
#include "Textrue.h"
#include "Shader.h"
#include "Material.h"
#include "Mesh.h"
#include "ResourceManager.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

#pragma region Comment Date : 2023-05-26 
/*
* Trouble : Fxing
* Date : 2023-05-26
* Author : yoseo
* 현재 SwapChain생성중 Warning 발생
* DXGI WARNING: IDXGIFactory::CreateSwapChain: Blt-model swap effects (DXGI_SWAP_EFFECT_DISCARD and DXGI_SWAP_EFFECT_SEQUENTIAL) are legacy swap effects that are predominantly superceded by their flip-model counterparts (DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL and DXGI_SWAP_EFFECT_FLIP_DISCARD). Please consider updating your application to leverage flip-model swap effects to benefit from modern presentation enhancements. More information is available at http://aka.ms/dxgiflipmodel. [ MISCELLANEOUS WARNING #294: ]*
* DXGI_SWAP_CHAIN_DESC 구조체의 swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
* 부분을 DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD 으로 교체하면 Warning은 사라지지만 프레임이 60으로 고정
* 되거나 혹은 떨어지는 현상이 발생한다.
* 해결하려고 시도중입니다.
* Date : 2023-05-29
* 아직진행중...
*/
#pragma endregion

namespace engine::graphics
{
#pragma region Constructor
	GraphicDeviceDX11::GraphicDeviceDX11(const HWND hWnd, const UINT screenWidth, const UINT screenHeight)
		: mConstantBuffers(nullptr)
	{
#ifdef _DEBUG
		const UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
		//둘중 어떤걸로 해야하는지 고민중...
		//const UINT deviceFlag = D3D11_CREATE_DEVICE_SINGLETHREADED;
		const UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#endif

#pragma region Create Device And Context
		D3D_FEATURE_LEVEL featureLevel = static_cast<D3D_FEATURE_LEVEL>(0);

		if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE,
			nullptr, deviceFlag, nullptr, 0, D3D11_SDK_VERSION,
			mDevice.GetAddressOf(), &featureLevel,
			mContext.GetAddressOf())))
		{
			MessageBox(hWnd, L"Failed to create device", L"Error", MB_OK);
			return;
		}
#pragma endregion

#pragma region Create SwaphChain
		DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

		swapChainDesc.BufferCount = 2;
		swapChainDesc.SampleDesc.Count = 1;
		swapChainDesc.SampleDesc.Quality = 0;
		swapChainDesc.OutputWindow = hWnd;
		swapChainDesc.Windowed = TRUE;

		swapChainDesc.BufferDesc.Width = screenWidth;
		swapChainDesc.BufferDesc.Height = screenHeight;
		swapChainDesc.BufferDesc.RefreshRate.Numerator = 240;   //최대프레임
		swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;   //최소프레임
		swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
		swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

		swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
		swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; //픽셀 포맷                                    

		Microsoft::WRL::ComPtr<IDXGIDevice> pDXGIDevice = nullptr;
		Microsoft::WRL::ComPtr<IDXGIAdapter> pDXGIAdapter = nullptr;
		Microsoft::WRL::ComPtr<IDXGIFactory> pDXGIFactory = nullptr;

		if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(pDXGIDevice.GetAddressOf()))))
		{
			MessageBox(hWnd, L"Failed to create IDXGIDevice", L"Error", MB_OK);
			assert(false);
			return;
		}

		if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(pDXGIAdapter.GetAddressOf()))))
		{
			MessageBox(hWnd, L"Failed to create IDXGIAdapter", L"Error", MB_OK);
			assert(false);
			return;
		}

		if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(pDXGIFactory.GetAddressOf()))))
		{
			MessageBox(hWnd, L"Failed to create IDXGIFactory", L"Error", MB_OK);
			assert(false);
			return;
		}

		if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), &swapChainDesc, mSwapChain.GetAddressOf())))
		{
			MessageBox(hWnd, L"Failed to create IDXGISwapChain", L"Error", MB_OK);
			assert(false);
			return;
		}



		//RenderTarget
		if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(mRenderTargetTexture.GetAddressOf()))))
		{
			MessageBox(hWnd, L"Failed to get buffer", L"Error", MB_OK);
			assert(false);
			return;
		}

		if (FAILED(mDevice->CreateRenderTargetView(mRenderTargetTexture.Get(), nullptr, mRenderTargetView.GetAddressOf())))
		{
			MessageBox(hWnd, L"Failed to create render target view", L"Error", MB_OK);
			assert(false);
			return;
		}
#pragma endregion

#pragma region Create DepthStencil
		D3D11_TEXTURE2D_DESC depthStencilDesc = {};

		depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
		depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
		depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
		depthStencilDesc.Width = screenWidth;
		depthStencilDesc.Height = screenHeight;
		depthStencilDesc.ArraySize = 1;
		depthStencilDesc.SampleDesc.Count = 1;
		depthStencilDesc.MiscFlags = 0;

		if (FAILED(mDevice->CreateTexture2D(&depthStencilDesc, nullptr, mDepthStencilTexture.GetAddressOf())))
		{
			MessageBox(hWnd, L"Failed to create depth stencil texture", L"Error", MB_OK);
			return;
		}

		if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilTexture.Get(), nullptr, mDepthStencilView.GetAddressOf())))
		{
			MessageBox(hWnd, L"Failed to create depth stencil view", L"Error", MB_OK);
			return;
		}
#pragma endregion

#pragma region Create ConstantBuffers		
		mConstantBuffers = new CBCollection(mDevice.Get());
#pragma endregion

#pragma region Create Sampler
		D3D11_SAMPLER_DESC tSamDesc = {};

		tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		tSamDesc.Filter = D3D11_FILTER_ANISOTROPIC;
		mDevice->CreateSamplerState(&tSamDesc, m_Sampler[0].GetAddressOf());


		tSamDesc.AddressU = D3D11_TEXTURE_ADDRESS_WRAP;
		tSamDesc.AddressV = D3D11_TEXTURE_ADDRESS_WRAP;
		tSamDesc.AddressW = D3D11_TEXTURE_ADDRESS_WRAP;
		tSamDesc.Filter = D3D11_FILTER_MIN_MAG_MIP_POINT;
		mDevice->CreateSamplerState(&tSamDesc, m_Sampler[1].GetAddressOf());

		mContext->VSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
		mContext->HSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
		mContext->DSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
		mContext->GSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());
		mContext->PSSetSamplers(0, 1, m_Sampler[0].GetAddressOf());


		mContext->VSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
		mContext->HSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
		mContext->DSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
		mContext->GSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
		mContext->PSSetSamplers(1, 1, m_Sampler[1].GetAddressOf());
#pragma endregion

	}
#pragma endregion

	GraphicDeviceDX11::~GraphicDeviceDX11()
	{
		SAFE_DELETE_POINTER(mConstantBuffers);
	}

	void GraphicDeviceDX11::BindIA(const Shader* const shader)
	{
		assert(shader);
		assert(shader->mInputLayout.Get());

		mContext->IASetInputLayout(shader->mInputLayout.Get());
		mContext->IASetPrimitiveTopology(shader->mTopology);
	}
	
	void GraphicDeviceDX11::BindMesh(const Mesh* const mesh)
	{
		assert(mesh);

		const UINT vertexSize = mesh->GetVertexSize();
		const UINT offset = 0;
		mContext->IASetVertexBuffers(0, 1, mesh->mBuffer.GetAddressOf(), &vertexSize, &offset);
	}
	
	void GraphicDeviceDX11::BindTexture(const Texture* texture, const UINT startSlot, const eShaderBindType stage)
	{
		switch (stage)
		{
		case eShaderBindType::VS:
			mContext->VSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
			break;
		case eShaderBindType::HS:
			mContext->HSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
			break;
		case eShaderBindType::DS:
			mContext->DSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
			break;
		case eShaderBindType::GS:
			mContext->GSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
			break;
		case eShaderBindType::PS:
			mContext->PSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
			break;
		case eShaderBindType::CS:
			mContext->CSSetShaderResources(startSlot, 1, texture->mSRV.GetAddressOf());
			break;
		default:
			assert(false);
			break;
		}
	}

	void GraphicDeviceDX11::BindCB(const eCBType type, const eShaderBindType stage)
	{
		const ConstantBuffer& CB = mConstantBuffers->GetConstantBuffer(type);
		const UINT startSlot = static_cast<UINT>(CB.mType);

		switch (stage)
		{
		case eShaderBindType::VS:
			mContext->VSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
			break;
		case eShaderBindType::HS:
			mContext->HSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
			break;
		case eShaderBindType::DS:
			mContext->DSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
			break;
		case eShaderBindType::GS:
			mContext->GSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
			break;
		case eShaderBindType::PS:
			mContext->PSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
			break;
		case eShaderBindType::CS:
			mContext->CSSetConstantBuffers(startSlot, 1, CB.mBuffer.GetAddressOf());
			break;
		default:
			assert(false);
			break;
		}
	}

	void GraphicDeviceDX11::PassCB(const eCBType type, const void* const data, const UINT byteSize)
	{
		assert(data);

		D3D11_MAPPED_SUBRESOURCE subResource = {};
		ConstantBuffer& CB = mConstantBuffers->GetConstantBuffer(type);

		assert(CB.mSize == byteSize);
		(void)byteSize;

		mContext->Map(CB.mBuffer.Get(), 0, D3D11_MAP::D3D11_MAP_WRITE_DISCARD, 0, &subResource);
		{
			memcpy_s(subResource.pData, CB.mDesc.ByteWidth, data, CB.mDesc.ByteWidth);
		}
		mContext->Unmap(CB.mBuffer.Get(), 0);
	}

	void GraphicDeviceDX11::BindVS(const Shader* const shader)
	{
		assert(shader);
		assert(shader->mVS.Get());

		mContext->VSSetShader(shader->mVS.Get(), nullptr, 0);
	}

	void GraphicDeviceDX11::BindPS(const Shader* const shader)
	{
		assert(shader);
		assert(shader->mPS.Get());

		mContext->PSSetShader(shader->mPS.Get(), nullptr, 0);
	}

	void GraphicDeviceDX11::Draw(const Mesh* const mesh, const UINT StartVertexLocation)
	{
		assert(mesh);

		const UINT vertexSize = mesh->GetVertexCount();
		mContext->Draw(vertexSize, StartVertexLocation);
	}

	void GraphicDeviceDX11::clearRenderTarget(const UINT screenWidth, const UINT screenHeight)
	{
		const FLOAT bgColor[4] = { 0.2f, 0.2f, 0.2f, 1.0f };
		const D3D11_VIEWPORT mViewPort =
		{
			0.0f, 0.0f,
			static_cast<FLOAT>(screenWidth), static_cast<FLOAT>(screenHeight),
			0.0f, 1.0f
		};
		mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
		mContext->RSSetViewports(1, &mViewPort);
		mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
		mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);
	}

	void GraphicDeviceDX11::present()
	{
		mSwapChain->Present(0, 0);
	}
}
