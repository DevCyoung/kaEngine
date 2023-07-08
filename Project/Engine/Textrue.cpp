#include "pch.h"
#include "Textrue.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "String.h"

#ifdef _DEBUG
#pragma comment(lib, "DirectXTex/Debug/DirectXTex_d.lib")
#else
#pragma comment(lib, "DirectXTex/Release/DirectXTex.lib")
#endif

Texture::Texture()	
	: mImage()
	, mTexture(nullptr)
	, mSRV(nullptr)
{
}

Texture::~Texture()
{
}

HRESULT Texture::Load(const std::wstring& fullPath)
{
	const std::wstring& FILE_EXTENSION = helper::String::SplitFilePathExtension(fullPath);

	if (FILE_EXTENSION == L".dds" || FILE_EXTENSION == L".DDS")
	{
		if (FAILED(LoadFromDDSFile(fullPath.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
		{
			Assert(false, L"fail load file .dds");
		}
	}
	else if (FILE_EXTENSION == L".tga" || FILE_EXTENSION == L".TGA")
	{
		if (FAILED(LoadFromTGAFile(fullPath.c_str(), nullptr, mImage)))
		{
			Assert(false, L"fail load file .tga");
		}
	}
	else if (FILE_EXTENSION == L".png" || FILE_EXTENSION == L".PNG" ||
		FILE_EXTENSION == L".jpg" || FILE_EXTENSION == L".JPG" ||
		FILE_EXTENSION == L".jpeg" || FILE_EXTENSION == L".JPEG" ||
		FILE_EXTENSION == L".bmp" || FILE_EXTENSION == L".BMP") // WIC (png, jpg, jpeg, bmp )
	{
		if (FAILED(LoadFromWICFile(fullPath.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
		{
			Assert(false, L"fail load file other");
		}
	}
	else
	{				
		Assert(false, L"is not supported");
	}

	if (FAILED(CreateShaderResourceView(gGraphicDevice->UnSafe_GetDevice()
		, mImage.GetImages()
		, mImage.GetImageCount()
		, mImage.GetMetadata(), mSRV.GetAddressOf())))
	{
		Assert(false, L"fail create resource view");
	}

	Assert(mSRV, WCHAR_IS_NULLPTR);

	mSRV->GetResource(reinterpret_cast<ID3D11Resource**>(mTexture.GetAddressOf()));
	return S_OK;
}
