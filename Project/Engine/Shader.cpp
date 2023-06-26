#include "pch.h"
#include "Shader.h"
#include "String.h"
#include "PathManager.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"


enum class eResShader;
const wchar_t* EnumResourcePath(eResShader type);

Shader::Shader(const eResShader vsFileName,
	const std::wstring& vsFunName,
	const eResShader psFileName,
	const std::wstring psFunName,
	const eRSType RSType,
	const eDSType DSType,
	const eBSType BSType)
	: Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
		vsFileName, vsFunName, psFileName, psFunName,
		RSType, DSType, BSType)
{
}

Shader::Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
	const eResShader vsFileName,
	const std::wstring& vsFunName,
	const eResShader psFileName,
	const std::wstring psFunName,
	const eRSType RSType,
	const eDSType DSType,
	const eBSType BSType)
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


	createVSShader(vsFileName, vsFunName);
	createPSShader(psFileName, psFunName);
}

Shader::~Shader()
{
}

void Shader::createShader(const eShaderBindType sType,
	const std::wstring& version,
	const eResShader fileName,
	const std::wstring& funName)
{
	Microsoft::WRL::ComPtr<ID3DBlob> vsBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> psBlob;
	Microsoft::WRL::ComPtr<ID3DBlob> errBlob;

	const std::string strFunName(String::WStrToStr(funName));
	const std::string strVersion(String::WStrToStr(version));


	std::wstring shaderPath = PathManager::GetInstance()->GetResourcePath();
	shaderPath += EnumResourcePath(fileName);
	(void)fileName;

	switch (sType)
	{
	case eShaderBindType::VS:
		if (FAILED(D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			strFunName.c_str(), strVersion.c_str(), 0, 0, vsBlob.GetAddressOf(), errBlob.GetAddressOf())))
		{
			Assert(false, L"failed to compile shader");
			return;
		}

		if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateVertexShader(vsBlob->GetBufferPointer(),
			vsBlob->GetBufferSize(), nullptr, mVS.GetAddressOf())))
		{
			Assert(false, L"failed to create vertex shader");
			return;
		}

		{
			//Input layout
			constexpr int MAX_INPUT_ELEMENT = 3;
			D3D11_INPUT_ELEMENT_DESC arrLayout[MAX_INPUT_ELEMENT] = {};

			arrLayout[0].AlignedByteOffset = 0;
			arrLayout[0].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32_FLOAT;
			arrLayout[0].InputSlot = 0;
			arrLayout[0].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			arrLayout[0].SemanticName = "POSITION";
			arrLayout[0].SemanticIndex = 0;

			arrLayout[1].AlignedByteOffset = 12;
			arrLayout[1].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32B32A32_FLOAT;
			arrLayout[1].InputSlot = 0;
			arrLayout[1].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			arrLayout[1].SemanticName = "COLOR";
			arrLayout[1].SemanticIndex = 0;

			arrLayout[2].AlignedByteOffset = 28;
			arrLayout[2].Format = DXGI_FORMAT::DXGI_FORMAT_R32G32_FLOAT;
			arrLayout[2].InputSlot = 0;
			arrLayout[2].InputSlotClass = D3D11_INPUT_CLASSIFICATION::D3D11_INPUT_PER_VERTEX_DATA;
			arrLayout[2].SemanticName = "TEXCOORD";
			arrLayout[2].SemanticIndex = 0;


			if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreateInputLayout(arrLayout, MAX_INPUT_ELEMENT
				, vsBlob->GetBufferPointer()
				, vsBlob->GetBufferSize()
				, mInputLayout.GetAddressOf())))
			{
				Assert(false, L"failed to create input layout");
				return;
			}
		}

		break;
	case eShaderBindType::HS:
		break;
	case eShaderBindType::DS:
		break;
	case eShaderBindType::GS:
		break;
	case eShaderBindType::PS:
		if (FAILED(D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			strFunName.c_str(), strVersion.c_str(), 0, 0, psBlob.GetAddressOf(), errBlob.GetAddressOf())))
		{
			Assert(false, L"failed to compile shader");
			return;
		}

		if (FAILED(gGraphicDevice->UnSafe_GetDevice()->CreatePixelShader(psBlob->GetBufferPointer(),
			psBlob->GetBufferSize(), nullptr, mPS.GetAddressOf())))
		{
			Assert(false, L"failed to create pixel shader");
			return;
		}

		break;
	default:
		Assert(false, WCHAR_IS_INVALID_TYPE);
		break;
	}
}

void Shader::createVSShader(const eResShader vsFileName, const std::wstring& vsFunName)
{
	Assert(!mVS.Get(), WCHAR_IS_NOT_NULLPTR);

	createShader(eShaderBindType::VS, L"vs_5_0", vsFileName, vsFunName);
}

void Shader::CreateHSShader(const eResShader hsFileName, const std::wstring& hsFunName)
{
	Assert(false, L"");
	(void)hsFileName;
	(void)hsFunName;

}

void Shader::CreateDSShader(const eResShader dsFileName, const std::wstring& dsFunName)
{
	Assert(false, L"");
	(void)dsFileName;
	(void)dsFunName;

}

void Shader::CreateGSShader(const eResShader gsFileName, const std::wstring& gsFunName)
{
	Assert(false, L"");
	(void)gsFileName;
	(void)gsFunName;
}

void Shader::createPSShader(const eResShader psFileName, const std::wstring& psFunName)
{
	Assert(!mPS.Get(), WCHAR_IS_NOT_NULLPTR);

	createShader(eShaderBindType::PS, L"ps_5_0", psFileName, psFunName);
}

HRESULT Shader::Load(const std::wstring& path)
{
	Assert(false, L"");
	(void)path;
	return E_NOTIMPL;
}
