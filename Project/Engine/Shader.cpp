#include "pch.h"
#include "Shader.h"
#include "String.h"
#include "PathManager.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"

const wchar_t* EnumResourcePath(eResShader type);

Shader::Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
	const std::wstring& VSRelativePath, const std::wstring& VSFunName,
	const std::wstring& PSRelativePath, const std::wstring& PSFunName,
	const eSMType SMType, const eRSType RSType, const eDSType DSType, const eBSType BSType)
	: Resource()
	, mTopology(topology)
	, mInputLayout(nullptr)
	, mVS(nullptr)
	, mHS(nullptr)
	, mDS(nullptr)
	, mGS(nullptr)
	, mPS(nullptr)
	, mRSType(RSType)
	, mDSType(DSType)
	, mBSType(BSType)
{
	Assert(eRSType::End != RSType, WCHAR_IS_INVALID_TYPE);
	Assert(eDSType::End != DSType, WCHAR_IS_INVALID_TYPE);
	Assert(eBSType::End != BSType, WCHAR_IS_INVALID_TYPE);

	createVSShader(VSRelativePath, VSFunName, SMType);
	createPSShader(PSRelativePath, PSFunName);
}

Shader::Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
	const eResShader VSRelativePath, const std::wstring& VSFunName,
	const eResShader PSRelativePath, const std::wstring& PSFunName,
	const eSMType SMType, const eRSType RSType, const eDSType DSType, const eBSType BSType)
	: Shader(topology,
		EnumResourcePath(VSRelativePath), VSFunName,
		EnumResourcePath(PSRelativePath), PSFunName,
		SMType, RSType, DSType, BSType)
{
}

Shader::~Shader()
{
}

void Shader::createVSShader(const std::wstring& VSRelativePath,
	const std::wstring& VSFunName,
	const eSMType SMType)
{
	Assert(!mVS.Get(), WCHAR_IS_NOT_NULLPTR);

	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> errBlob;

	shaderCompile(VSRelativePath, VSFunName, L"vs_5_0", vsBlob.GetAddressOf(), errBlob.GetAddressOf());

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateVertexShader(vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(), nullptr, mVS.GetAddressOf())))
	{
		OutputDebugStringA(reinterpret_cast<LPCSTR>((errBlob)->GetBufferPointer()));
		Assert(false, L"failed to create vertex shader");
		return;
	}

	const SMCollection* const P_SM_COLLECTION = gGraphicDevice->GetIEDCollection();
	const UINT INPUT_ELEMENT_COUNT = static_cast<UINT>(P_SM_COLLECTION->GetInputElementCount(SMType));
	const D3D11_INPUT_ELEMENT_DESC* const P_SM_DATA = P_SM_COLLECTION->GetInputElementDatas(SMType);

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateInputLayout(P_SM_DATA,
		INPUT_ELEMENT_COUNT,
		vsBlob->GetBufferPointer(),
		vsBlob->GetBufferSize(),
		mInputLayout.GetAddressOf())))
	{
		Assert(false, L"failed to create input layout");
		return;
	}
}

void Shader::createPSShader(const std::wstring& PSRelativePath, const std::wstring& PSFunName)
{
	Assert(!mPS.Get(), WCHAR_IS_NOT_NULLPTR);

	Microsoft::WRL::ComPtr<ID3DBlob> psBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> errBlob;

	shaderCompile(PSRelativePath, PSFunName, L"ps_5_0", psBlob.GetAddressOf(), errBlob.GetAddressOf());

	if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreatePixelShader(psBlob->GetBufferPointer(),
		psBlob->GetBufferSize(),
		nullptr,
		mPS.GetAddressOf())))
	{
		OutputDebugStringA(reinterpret_cast<LPCSTR>((errBlob)->GetBufferPointer()));
		Assert(false, L"failed to create pixel shader");
		return;
	}
}

void Shader::shaderCompile(const std::wstring& relativePath,
	const std::wstring& funName,
	const std::wstring& version,
	ID3DBlob** const ppBlob,
	ID3DBlob** const ppErrorBlob)
{
	const std::wstring& SHADER_FULL_PATH = PathManager::GetInstance()->GetResourcePath() + relativePath;
	const std::string& FUN_NAME = helper::String::WStrToStr(funName);
	const std::string& VERSION_NAME = helper::String::WStrToStr(version);

	if (FAILED(D3DCompileFromFile(SHADER_FULL_PATH.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
		FUN_NAME.c_str(), VERSION_NAME.c_str(), 0, 0, ppBlob, ppErrorBlob)))
	{
		OutputDebugStringA(reinterpret_cast<LPCSTR>((*ppErrorBlob)->GetBufferPointer()));
		Assert(false, L"failed to compile shader");
		return;
	}
}

HRESULT Shader::Load(const std::wstring& fullPath)
{
	Assert(false, L"");

	(void)fullPath;
	return E_NOTIMPL;
}
