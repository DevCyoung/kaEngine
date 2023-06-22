#pragma once
#include <wrl.h>
#include <d3d11.h>	
#include "DirectXTex.h"
#include "Resource.h"

namespace engine
{
	namespace graphics
	{
		class GraphicDeviceDX11;
	}

	class Texture : public Resource
	{				
		friend class ResourceManager;
		friend class graphics::GraphicDeviceDX11;
	public:		

	private:
		Texture();
		virtual ~Texture();
		Texture(const Texture&) = delete;
		Texture& operator=(const Texture&) = delete;	
		virtual HRESULT Load(const std::wstring& path) override;		


	private:
		D3D11_TEXTURE2D_DESC mDesc;
		ScratchImage mImage;
		Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
		Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;

		//Comment: 추후에 작업해야함
		//Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;
		//Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilTexture;
		//Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;		
	};
}
