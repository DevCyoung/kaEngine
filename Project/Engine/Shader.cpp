#include "pch.h"
#include "Shader.h"
#include "String.h"
#include "PathManager.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

const wchar_t* EnumResourcePath(eResShader type);

Shader::Shader(const D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY,
	const std::wstring& VS_RELATIVE_PATH, const std::wstring& VS_FUN_NAME,
	const std::wstring& PS_RELATIVE_PATH, const std::wstring& PS_FUN_NAME,
	const eIEDType IED_TYPE, const eRSType RS_TYPE, const eDSType DS_TYPE, const eBSType BS_TYPE)
	: Resource()
	, mTopology(TOPOLOGY)
	, mInputLayout(nullptr)
	, mVS(nullptr)
	, mHS(nullptr)
	, mDS(nullptr)
	, mGS(nullptr)
	, mPS(nullptr)
	, mRSType(RS_TYPE)
	, mDSType(DS_TYPE)
	, mBSType(BS_TYPE)
{
	Assert(eRSType::End != RS_TYPE, WCHAR_IS_INVALID_TYPE);
	Assert(eDSType::End != DS_TYPE, WCHAR_IS_INVALID_TYPE);
	Assert(eBSType::End != BS_TYPE, WCHAR_IS_INVALID_TYPE);

	createVSShader(VS_RELATIVE_PATH, VS_FUN_NAME, IED_TYPE);
	createPSShader(PS_RELATIVE_PATH, PS_FUN_NAME);
}

Shader::Shader(const D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY,
	const eResShader VS_RELATIVE_PATH_TYPE, const std::wstring& VS_FUN_NAME,
	const eResShader PS_RELATIVE_PATH_TYPE, const std::wstring& PS_FUN_NAME,
	const eIEDType IED_TYPE, const eRSType RS_TYPE, const eDSType DS_TYPE, const eBSType BS_TYPE)
	: Shader(TOPOLOGY,
		EnumResourcePath(VS_RELATIVE_PATH_TYPE), VS_FUN_NAME,
		EnumResourcePath(PS_RELATIVE_PATH_TYPE), PS_FUN_NAME,
		IED_TYPE, RS_TYPE, DS_TYPE, BS_TYPE)
{
}

Shader::~Shader()
{
}

void Shader::createVSShader(const std::wstring& VS_RELATIVE_PATH, const std::wstring& VS_FUN_NAME, const eIEDType& IED_TYPE)
{
	Assert(!mVS.Get(), WCHAR_IS_NOT_NULLPTR);

	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> errBlob;

	shaderCompile(VS_RELATIVE_PATH, VS_FUN_NAME, L"vs_5_0", vsBlob.GetAddressOf(), errBlob.GetAddressOf());

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateVertexShader(vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(), nullptr, mVS.GetAddressOf())))
	{
		Assert(false, L"failed to create vertex shader");
		return;
	}

	const IEDCollection* const P_IED_COLLECTION = gGraphicDevice->GetIEDCollection();

	const UINT MAX_INPUT_ELEMENT = static_cast<UINT>(P_IED_COLLECTION->GetIEDSize(IED_TYPE));
	const D3D11_INPUT_ELEMENT_DESC* const P_IED_DATA = P_IED_COLLECTION->GetData(IED_TYPE);

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateInputLayout(P_IED_DATA,
		MAX_INPUT_ELEMENT,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		mInputLayout.GetAddressOf())))
	{
		Assert(false, L"failed to create input layout");
		return;
	}
}

void Shader::createPSShader(const std::wstring& PS_RELATIVE_PATH, const std::wstring& PS_FUN_NAME)
{
	Assert(!mPS.Get(), WCHAR_IS_NOT_NULLPTR);

	Microsoft::WRL::ComPtr<ID3DBlob> psBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> errBlob;

	shaderCompile(PS_RELATIVE_PATH, PS_FUN_NAME, L"ps_5_0", psBlob.GetAddressOf(), errBlob.GetAddressOf());

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreatePixelShader(psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(),
		nullptr,
		mPS.GetAddressOf())))
	{
		Assert(false, L"failed to create pixel shader");
		return;
	}
}

void Shader::shaderCompile(const std::wstring& RELATIVE_PATH,
	const std::wstring& FUN_NAME,
	const std::wstring& VERSION,
	ID3DBlob** const blob,
	ID3DBlob** const errorBlob)
{
	const std::wstring& SHADER_FULL_PATH = PathManager::GetInstance()->GetResourcePath() + RELATIVE_PATH;
	const std::string STR_FUN_NAME(helper::String::WStrToStr(FUN_NAME));
	const std::string STR_VERSION_NAME(helper::String::WStrToStr(VERSION));

	if (FAILED(D3DCompileFromFile(SHADER_FULL_PATH.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		STR_FUN_NAME.c_str(), STR_VERSION_NAME.c_str(), 0, 0, blob, errorBlob)))
	{
		Assert(false, L"failed to compile shader");
		return;
	}
}


HRESULT Shader::Load(const std::wstring& FULL_PATH)
{
	Assert(false, L"");

	(void)FULL_PATH;
	return E_NOTIMPL;
}
