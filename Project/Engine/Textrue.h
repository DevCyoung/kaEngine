#pragma once
#include <wrl.h>
#include <d3d11.h>	
#include "Resource.h"
#include "DirectXTex.h"

class Texture : public Resource
{
	friend class ResourceManager;
	friend class GraphicDeviceDX11;

public:
	Texture(UINT _Width, UINT _Height, DXGI_FORMAT _pixelformat
		, UINT _BindFlag, D3D11_USAGE _Usage);
	Texture();
	virtual ~Texture();
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;
public:
	float GetWidth() const { return static_cast<float>(mWidth); }
	float GetHeight() const { return static_cast<float>(mHeight); }

	virtual HRESULT Load(const std::wstring& filePath) override;

private:
	ScratchImage mImage;
	UINT mWidth;
	UINT mHeight;
	Microsoft::WRL::ComPtr<ID3D11Texture2D>				mTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView>	mSRV;
	Microsoft::WRL::ComPtr<ID3D11RenderTargetView>	    mRTV;
	Microsoft::WRL::ComPtr<ID3D11DepthStencilView>	    mDSV;
	Microsoft::WRL::ComPtr<ID3D11UnorderedAccessView>   mUAV;
};
