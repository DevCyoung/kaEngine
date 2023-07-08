#pragma once
#include <wrl.h>
#include <d3d11.h>	
#include "Resource.h"
#include "DirectXTex.h"

class Texture : public Resource
{
	friend class ResourceManager;
	friend class GraphicDeviceDX11;

private:
	Texture();
	virtual ~Texture();
	Texture(const Texture&) = delete;
	Texture& operator=(const Texture&) = delete;		
public:
	float GetWidth() const {  return static_cast<float>(mImage.GetMetadata().width);  }
	float GetHeight() const { return static_cast<float>(mImage.GetMetadata().height); }

	virtual HRESULT Load(const std::wstring& fullPath) override;

private:	
	ScratchImage mImage;
	Microsoft::WRL::ComPtr<ID3D11Texture2D> mTexture;
	Microsoft::WRL::ComPtr<ID3D11ShaderResourceView> mSRV;
};
