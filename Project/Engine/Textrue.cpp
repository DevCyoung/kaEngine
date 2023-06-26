#include "pch.h"
#include "Textrue.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

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

HRESULT Texture::Load(const std::wstring& path)
{
	constexpr UINT PATH_LEN = 256;
	wchar_t szExtension[PATH_LEN] = { 0, };
	errno_t err =
		_wsplitpath_s(path.c_str(), nullptr, 0, nullptr, 0, nullptr, 0, szExtension, PATH_LEN);
	(void)(err);
	Assert(!err, L"error");

	std::wstring extension = szExtension;
	if (extension == L".dds" || extension == L".DDS")
	{
		if (FAILED(LoadFromDDSFile(path.c_str(), DDS_FLAGS::DDS_FLAGS_NONE, nullptr, mImage)))
		{
			Assert(false, L"fail load file .dds");
		}
	}
	else if (extension == L".tga" || extension == L".TGA")
	{
		if (FAILED(LoadFromTGAFile(path.c_str(), nullptr, mImage)))
		{
			Assert(false, L"fail load file .tga");
		}
	}
	else if (extension == L".png" || extension == L".PNG" ||
		extension == L".jpg" || extension == L".JPG" ||
		extension == L".jpeg" || extension == L".JPEG" ||
		extension == L".bmp" || extension == L".BMP") // WIC (png, jpg, jpeg, bmp )
	{
		if (FAILED(LoadFromWICFile(path.c_str(), WIC_FLAGS::WIC_FLAGS_NONE, nullptr, mImage)))
		{
			Assert(false, L"fail load file other");
		}
	}
	else
	{
		extension += L" is not supported";
		Assert(false, extension.c_str());
	}

	//gEngine->GetGraphicDevice()
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
