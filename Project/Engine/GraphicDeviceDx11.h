#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

namespace engine
{
	class CBCollection;
	class ShaderCollection;
	class Shader;

	enum class eShaderType;
	enum class eCBType;	
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
		GraphicDeviceDX11();
		virtual ~GraphicDeviceDX11();	
		void BindIA(const eShaderType type);
		void BindVS(const eShaderType type);
		void BindPS(const eShaderType type);
		void PassCB(const eCBType type, const void* const data);
		void BindCB(const eCBType type, const eShaderStage stage);
		//void BindVB();
		void Draw();

	private:
		void clearRenderTarget();
		void present();
		//void BindConstantBuffer();
		//void BindRenderTarget(const Texture& texture);
		//void BindPixelShader(const Shader& pixelShader);
		//void BindVertexShader(const Shader& vertexShader);

	private:
		Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
		Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTargetTexture;
		Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilTexture;
		Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;

		Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;

		Microsoft::WRL::ComPtr<ID3D11Buffer> triangleBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> rectBuffer;
		Microsoft::WRL::ComPtr<ID3D11Buffer> shapeBuffers[1000];

		CBCollection*	mConstantBuffers;
		ShaderCollection* mShaders;
	};
}