#include "pch.h"
#include "String.h"
#include "Shader.h"
#include "PathManager.h"

namespace engine
{
	enum class eResShader;
	const wchar_t* EnumResourcePath(eResShader type);

	Shader::Shader(const eResShader vsFileName,
		const std::wstring& vsFunName,
		const eResShader psFileName,
		const std::wstring psFunName,
		ID3D11Device* const device,
		const HWND hWnd)
		: Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
			vsFileName, vsFunName, psFileName, psFunName, device, hWnd)
	{
	}

	Shader::Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
		const eResShader vsFileName,
		const std::wstring& vsFunName,
		const eResShader psFileName,
		const std::wstring psFunName,
		ID3D11Device* const device,
		const HWND hWnd)
		: Resource()
		, mTopology(topology)
		, mInputLayout(nullptr)
		, mVS(nullptr)
		, mHS(nullptr)
		, mDS(nullptr)
		, mGS(nullptr)
		, mPS(nullptr)
	{
		createVSShader(vsFileName, vsFunName, device, hWnd);
		createPSShader(psFileName, psFunName, device, hWnd);
	}

	Shader::~Shader()
	{
	}

	void Shader::createShader(const eShaderBindType sType,
		const std::wstring& version,
		const eResShader fileName,
		const std::wstring& funName,
		ID3D11Device* const device,
		const HWND hWnd)
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
				MessageBox(hWnd, L"Failed to compile shader", L"Error", MB_OK);
				assert(false);
				return;
			}

			if (FAILED(device->CreateVertexShader(vsBlob->GetBufferPointer(),
				vsBlob->GetBufferSize(), nullptr, mVS.GetAddressOf())))
			{
				MessageBox(hWnd, L"Failed to create vertex shader", L"Error", MB_OK);
				assert(false);
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


				if (FAILED(device->CreateInputLayout(arrLayout, MAX_INPUT_ELEMENT
					, vsBlob->GetBufferPointer()
					, vsBlob->GetBufferSize()
					, mInputLayout.GetAddressOf())))
				{
					MessageBox(hWnd, L"Failed to create input layout", L"Error", MB_OK);
					assert(false);
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
				MessageBox(hWnd, L"Failed to compile shader", L"Error", MB_OK);
				assert(false);
				return;
			}

			if (FAILED(device->CreatePixelShader(psBlob->GetBufferPointer(),
				psBlob->GetBufferSize(), nullptr, mPS.GetAddressOf())))
			{
				MessageBox(hWnd, L"Failed to create pixel shader", L"Error", MB_OK);
				assert(false);
				return;
			}

			break;
		default:
			break;
		}
	}

	void Shader::createVSShader(const eResShader vsFileName,
		const std::wstring& vsFunName,
		ID3D11Device* const device,
		const HWND hWnd)
	{
		assert(!mVS.Get());
		createShader(eShaderBindType::VS, L"vs_5_0", vsFileName, vsFunName, device, hWnd);
	}

	void Shader::CreateHSShader(const eResShader hsFileName,
		const std::wstring& hsFunName,
		ID3D11Device* const device,
		const HWND hWnd)
	{
		assert(nullptr);
		(void)hsFileName;
		(void)hsFunName;
		(void)device;
		(void)hWnd;
	}

	void Shader::CreateDSShader(const eResShader dsFileName,
		const std::wstring& dsFunName,
		ID3D11Device* const device,
		const HWND hWnd)
	{
		assert(nullptr);
		(void)dsFileName;
		(void)dsFunName;
		(void)device;
		(void)hWnd;
	}

	void Shader::CreateGSShader(const eResShader gsFileName,
		const std::wstring& gsFunName,
		ID3D11Device* const device,
		const HWND hWnd)
	{
		assert(nullptr);
		(void)gsFileName;
		(void)gsFunName;
		(void)device;
		(void)hWnd;
	}

	void Shader::createPSShader(const eResShader psFileName,
		const std::wstring& psFunName,
		ID3D11Device* const device,
		const HWND hWnd)
	{
		assert(!mPS.Get());
		createShader(eShaderBindType::PS, L"ps_5_0", psFileName, psFunName, device, hWnd);
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		assert(false);
		(void)path;
		return E_NOTIMPL;
	}
}
