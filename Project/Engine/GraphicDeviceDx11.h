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
	enum class eMeshType;
	enum class eShaderType;
	enum class eShaderBindType;

	enum class eResTexture;

	namespace graphics
	{
		class GraphicDeviceDX11
		{
			friend class Engine;
		public:
			GraphicDeviceDX11(const HWND hWnd, const UINT screenWidth, const UINT screenHeight);
			virtual ~GraphicDeviceDX11();
			GraphicDeviceDX11(const GraphicDeviceDX11&) = delete;
			GraphicDeviceDX11& operator=(const GraphicDeviceDX11&) = delete;
			ID3D11Device* const GetDevice() { return mDevice.Get(); }

					

			void BindIA(const eShaderType type);
			void BindVS(const eShaderType type);
			void BindPS(const eShaderType type);
			void BindCB(const eCBType type, const eShaderBindType stage);
			void BindMesh(const eMeshType type);
			void BindTexture(const eResTexture texture, const eShaderBindType stage);

			void PassCB(const eCBType type, const void* const data);

			void Draw(const eMeshType type, const UINT StartVertexLocation);
			//void DrawIndexd();

		private:
			void clearRenderTarget(const UINT screenWidth, const UINT screenHeight);
			
			void present();

		private:
			Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
			Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;
			Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTargetTexture;
			Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
			Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilTexture;
			Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
			Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;			
			Microsoft::WRL::ComPtr<ID3D11SamplerState> m_Sampler[2];

			MeshCollection* mMeshs;
			ShaderCollection* mShaders;
			CBCollection* mConstantBuffers;
		};
	}
}
