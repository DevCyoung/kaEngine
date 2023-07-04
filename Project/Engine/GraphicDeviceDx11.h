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
	GraphicDeviceDX11(const HWND H_WINDOW, const UINT RENDER_TARGET_WIDTH, const UINT RENDER_TARGET_HEIGHT);
	virtual ~GraphicDeviceDX11();
	GraphicDeviceDX11(const GraphicDeviceDX11&) = delete;
	GraphicDeviceDX11& operator=(const GraphicDeviceDX11&) = delete;

	ID3D11Device* UnSafe_GetDevice() const { Assert(mDevice, WCHAR_IS_NULLPTR); return mDevice.Get(); }

	void BindIA(const Shader* const P_SHADER) const;
	void BindMesh(const Mesh* const P_MESH) const;
	void BindTexture(const eShaderBindType SHADER_BIND_STAGE_TYPE,
		const UINT START_SLOT,
		const Texture* const P_TEXTURE) const;
	void BindCB(const eCBType CB_TYPE, const eShaderBindType SHADER_BIND_STAGE_TYPE) const;
	void PassCB(const eCBType CB_TYPE, const UINT BYTE_SIZE, const void* const P_DATA) const;
	void BindVS(const Shader* const P_SHADER) const;
	void BindPS(const Shader* const P_SHADER) const;
	void BindBS(const eBSType BS_TYPE) const;
	void BindDS(const eDSType DS_TYPE) const;
	void BindRS(const eRSType RS_TYPE) const;

	void Draw(const Mesh* const P_MESH) const;
	void ClearRenderTarget(const UINT RENDER_TARGET_WIDTH,
		const UINT RENDER_TARGET_HEIGHT,
		const FLOAT BG_COLOR[4],
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

