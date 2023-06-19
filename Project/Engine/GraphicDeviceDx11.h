#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

struct ID3D11Device;

namespace engine
{
	enum class eCBType;		
	enum class eShaderBindType;	

	class CBCollection;
	class Shader;
	class Mesh;
	class Texture;	

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
			
			ID3D11Device* UnSafe_GetDevice() const { return mDevice.Get(); }
				
			void BindIA(const Shader* const shader);
			void BindVS(const Shader* const shader);
			void BindPS(const Shader* const shader);
			void BindCB(const eCBType type, const eShaderBindType stage);
			void BindMesh(const Mesh* const mesh);
			void BindTexture(const Texture* texture, const UINT startSlot, const eShaderBindType stage);

			void PassCB(const eCBType type, const void* const data, const UINT byteSize);

			void Draw(const Mesh* const mesh, const UINT StartVertexLocation);
			//void DrawIndexd();

		private:
			void clearRenderTarget(const UINT screenWidth, const UINT screenHeight);
			void engineResourceLoad(const HWND hWnd);
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
			
			CBCollection* mConstantBuffers;
		};
	}
}