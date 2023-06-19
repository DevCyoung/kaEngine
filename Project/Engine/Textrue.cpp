#include "pch.h"
#include "Textrue.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/DirectXTex_d.lib")
#else
#pragma comment(lib, "DirectXTex/DirectXTex.lib")
#endif

namespace engine
{
	Texture::Texture()
		: mDesc{}
		, mImage()
		, mTexture(nullptr)
		, mSRV(nullptr)
	{
	}

	Texture::~Texture()
	{
	}

	HRESULT Texture::Load(const std::wstring& path)
	{	
		const UINT wByteSize = 256;
		wchar_t szExtension[wByteSize] = {0,};
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, wByteSize);

		std::wstring extension = szExtension;
		if (extension == L".dds" || extension == L".DDS")
		{
			if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
			{
				assert(false);
			}				
		}		
		else if (extension == L".tga" || extension == L".TGA")
		{
			if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
			{
				assert(false);
			}
		}
		else if (extension == L".png"  || extension == L".PNG"  || 
			     extension == L".jpg"  || extension == L".JPG"  ||
				 extension == L".jpeg" || extension == L".JPEG" || 
				 extension == L".bmp"  || extension == L".BMP") // WIC (png, jpg, jpeg, bmp )
		{
			if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
			{
				assert(false);
			}				
		}
		else
		{
			assert(false);
		}

		CreateShaderResourceView (gGraphicDevice->GetDevice(), mImage.GetImages(), mImage.GetImageCount()
			, mImage.GetMetadata(), mSRV.GetAddressOf() );
		
		mSRV->GetResource(reinterpret_cast<ID3D11Resource**>(mTexture.GetAddressOf()));

		return S_OK;
	}
}