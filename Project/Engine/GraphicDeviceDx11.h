#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

struct ID3D11Device;


enum class eShaderBindType;
enum class eCBType;
enum class eBSType;
enum class eDSType;
enum class eRSType;

class CBCollection;
class RSCollection;
class BSCollection;
class DSCollection;

class Shader;
class Mesh;
class Texture;


class GraphicDeviceDX11
{
	friend class Engine;
public:
	GraphicDeviceDX11(const HWND hWnd, const UINT screenWidth, const UINT screenHeight);
	virtual ~GraphicDeviceDX11();
	GraphicDeviceDX11(const GraphicDeviceDX11&) = delete;
	GraphicDeviceDX11& operator=(const GraphicDeviceDX11&) = delete;

	ID3D11Device* UnSafe_GetDevice() const { Assert(mDevice, WCHAR_IS_NULLPTR); return mDevice.Get(); }

	void BindIA(const Shader* const shader) const;
	void BindMesh(const Mesh* const mesh) const;
	void BindTexture(const eShaderBindType stage, const UINT startSlot, const Texture* const texture) const;
	void BindCB(const eCBType type, const eShaderBindType stage) const;
	void PassCB(const eCBType type, const UINT byteSize, const void* const data) const;
	void BindVS(const Shader* const shader) const;
	void BindPS(const Shader* const shader) const;
	void BindBS(const eBSType type) const;
	void BindDS(const eDSType type) const;
	void BindRS(const eRSType type) const;

	void Draw(const Mesh* const mesh) const;
	//void DrawIndexd();
	void ClearRenderTarget(const UINT screenWidth,
		const UINT screenHeight,
		const FLOAT bgColor[4],
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> renderTargetView,
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> depthStencilView) const;

private:
	void present();

	Microsoft::WRL::ComPtr<ID3D11RenderTargetView> GetRenderTargetView() const
	{
		Assert(mRenderTargetView, WCHAR_IS_NULLPTR);

		return mRenderTargetView;
	}
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView> GetDepthStencilView() const
	{
		Assert(mDepthStencilView, WCHAR_IS_NULLPTR);

		return mDepthStencilView;
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
};

