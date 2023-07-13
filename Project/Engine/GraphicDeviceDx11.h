#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

class CBCollection;
class RSCollection;
class BSCollection;
class DSCollection;
class SMCollection;
class Shader;
class Mesh;
class Texture;

struct ID3D11Device;

enum class eCBType;
enum class eRSType;
enum class eBSType;
enum class eDSType;
enum class eShaderBindType;

class GraphicDeviceDX11
{
	friend class Engine;
private:
	GraphicDeviceDX11(const HWND hWnd, const UINT renderTargetWidth, const UINT renderTargetHeight);
	virtual ~GraphicDeviceDX11();
	GraphicDeviceDX11(const GraphicDeviceDX11&) = delete;
	GraphicDeviceDX11& operator=(const GraphicDeviceDX11&) = delete;

public:
	ID3D11Device* UnSafe_GetDevice() const { Assert(mDevice, WCHAR_IS_NULLPTR); return mDevice.Get(); }

	void BindIA(const Shader* const shader) const;
	void BindMesh(const Mesh* const mesh) const;
	void BindTexture(const eShaderBindType stageType, const UINT startSlot, const Texture* const texture) const;
	void BindCB(const eCBType CBType, const eShaderBindType stageType) const;
	void PassCB(const eCBType CBType, const UINT dataSize, const void* const data) const;
	void BindVS(const Shader* const shader) const;
	void BindPS(const Shader* const shader) const;
	void BindBS(const eBSType BSType) const;
	void BindDS(const eDSType DSType) const;
	void BindRS(const eRSType RSType) const;
	void BindRenderTarget(const UINT renderTargetWidth,
		const UINT renderTargetHeight,
		ID3D11RenderTargetView* const* const ppRnderTargetView,
		ID3D11DepthStencilView* const depthStencilView) const;

	void Draw(const Mesh* const mesh) const;

	void ClearRenderTarget(ID3D11RenderTargetView* const* const ppRnderTargetView,
		ID3D11DepthStencilView* const depthStencilView,
		const FLOAT backgroundColor[4]) const;

	const SMCollection* GetIEDCollection() const 
	{ 
		Assert(mSMCollection, WCHAR_IS_NULLPTR);
		return mSMCollection;
	}

private:
	void present();

	ID3D11RenderTargetView** GetRenderTargetViewAddressOf()
	{		
		Assert(mRenderTargetView, WCHAR_IS_NULLPTR);

		return mRenderTargetView.GetAddressOf();
	}

	ID3D11DepthStencilView* GetDepthStencilView()
	{
		Assert(mDepthStencilView, WCHAR_IS_NULLPTR);

		return mDepthStencilView.Get();
	}

private:
	Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
	Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTargetTexture;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilTexture;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
	Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
	Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler[2];

	CBCollection* mCBCollection;
	RSCollection* mRSCollection;
	BSCollection* mBSCollection;
	DSCollection* mDSCollection;
	SMCollection* mSMCollection;
};

