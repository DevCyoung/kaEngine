#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

namespace engine
{
	class MeshCollection;
	class ShaderCollection;
	class CBCollection;

	enum class eCBType;
	enum class eShaderType;	
	enum class eShaderStage
	{
		VS, HS, DS, GS, PS, CS, End,
	};
}

namespace engine::graphics
{
	struct tTransform
	{
		Vector4 pos;
	};

	class GraphicDeviceDX11
	{
		friend class Engine;
	public:
		GraphicDeviceDX11(const HWND hWnd, const UINT screenWidth, const UINT screenHeight);
		virtual ~GraphicDeviceDX11();	
		void BindIA(const eShaderType type);
		void BindVS(const eShaderType type);
		void BindPS(const eShaderType type);
		void PassCB(const eCBType type, const void* const data);
		void BindCB(const eCBType type, const eShaderStage stage);
		void Draw();

	private:
		void clearRenderTarget();
		void present();

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTargetTexture;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilTexture;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
//
		Microsoft::WRL::ComPtr<ID3D11Buffer> triangleBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> rectBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> shapeBuffers[1000];
//
		MeshCollection* mMeshs;
		ShaderCollection* mShaders;
		CBCollection*	mConstantBuffers;
	};
}

