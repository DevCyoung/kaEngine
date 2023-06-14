#include "pch.h"
#include "Shader.h"
#include "String.h"

//#include "Engine.h"

namespace engine
{
	Shader::Shader(const std::wstring& vsFileName, const std::wstring& vsFunName, 
		const std::wstring& psFileName, const std::wstring psFunName)
		: Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST, 
			vsFileName, vsFunName, psFileName, psFunName)
	{
	}

	Shader::Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
		const std::wstring& vsFileName, const std::wstring& vsFunName,
		const std::wstring& psFileName, const std::wstring psFunName)
		: Resource()
		, mTopology(topology)
		, mInputLayout(nullptr)		
		, mVS(nullptr)
		, mHS(nullptr)
		, mDS(nullptr)
		, mGS(nullptr)
		, mPS(nullptr)
	{		
		createVSShader(vsFileName, vsFunName);
		createPSShader(psFileName, psFunName);		
	}

	Shader::~Shader()
	{
	}

	void Shader::createShader(const eShaderType sType, const std::wstring& version,
		const std::wstring& fileName, const std::wstring& funName)
	{
		Microsoft::WRL::ComPtr<ID3DBlob> vsBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> psBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> errBlob;
		
		const HWND hWnd = gEngine->GetHwnd();
		const std::string strFunName(String::WStrToStr(funName));
		const std::string strVersion(String::WStrToStr(version));

		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader\\";
		shaderPath += fileName;

		switch (sType)
		{
		case eShaderType::VS:

			if (FAILED(D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
				strFunName.c_str(), strVersion.c_str(), 0, 0, vsBlob.GetAddressOf(), errBlob.GetAddressOf())))
			{
				MessageBox(hWnd, L"Failed to compile shader", L"Error", MB_OK);
				return;
			}

			if (FAILED(gDevie->CreateVertexShader(vsBlob->GetBufferPointer(),
				vsBlob->GetBufferSize(), nullptr, mVS.GetAddressOf())))
			{
				MessageBox(hWnd, L"Failed to create vertex shader", L"Error", MB_OK);
				return;
			}
			
			{
				//Input layout
				constexpr int MAX_INPUT_ELEMENT = 2;
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


				if (FAILED(gDevie->CreateInputLayout(arrLayout, MAX_INPUT_ELEMENT
					, vsBlob->GetBufferPointer()
					, vsBlob->GetBufferSize()
					, mInputLayout.GetAddressOf())))
				{
					MessageBox(hWnd, L"Failed to create input layout", L"Error", MB_OK);
					return;
				}
			}
		
			break;
		case eShaderType::HS:
			break;
		case eShaderType::DS:
			break;
		case eShaderType::GS:
			break;
		case eShaderType::PS:
			if (FAILED(D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
				strFunName.c_str(), strVersion.c_str(), 0, 0, psBlob.GetAddressOf(), errBlob.GetAddressOf())))
			{
				MessageBox(hWnd, L"Failed to compile shader", L"Error", MB_OK);
				return;
			}

			if (FAILED(gDevie->CreatePixelShader(psBlob->GetBufferPointer(),
				psBlob->GetBufferSize(), nullptr, mPS.GetAddressOf())))
			{
				MessageBox(hWnd, L"Failed to create pixel shader", L"Error", MB_OK);
				return;
			}
		
			break;
		default:
			break;
		}
	}

	inline void Shader::createVSShader(const std::wstring& vsFileName, const std::wstring& vsFunName)
	{
		assert(!mVS.Get());
		createShader(eShaderType::VS, L"vs_5_0", vsFileName, vsFunName);
	}

	inline void Shader::CreateHSShader(const std::wstring& hsFileName, const std::wstring& hsFunName)
	{
		assert(nullptr);
		(void)hsFileName;
		(void)hsFunName;

	}

	inline void Shader::CreateDSShader(const std::wstring& dsFileName, const std::wstring& dsFunName)
	{
		assert(nullptr);
		(void)dsFileName;
		(void)dsFunName;

	}

	inline void Shader::CreateGSShader(const std::wstring& gsFileName, const std::wstring& gsFunName)
	{
		assert(nullptr);
		(void)gsFileName;
		(void)gsFunName;
	}

	inline void Shader::createPSShader(const std::wstring& psFileName, const std::wstring& psFunName)
	{
		assert(!mPS.Get());
		createShader(eShaderType::PS, L"ps_5_0", psFileName, psFunName);
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		(void)path;
		return E_NOTIMPL;
	}
}
