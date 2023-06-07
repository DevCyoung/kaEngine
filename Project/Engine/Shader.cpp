#include "Shader.h"


#include "String.h"

namespace engine
{
	Shader::Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
		const std::wstring& vsFileName, const std::wstring& vsFunName,
		const std::wstring& psFileName, const std::wstring psFunName)
		: mTopology(topology)
		, mInputLayout(nullptr)
		, mVSBlob(nullptr)
		, mHSBlob(nullptr)
		, mDSBlob(nullptr)
		, mGSBlob(nullptr)
		, mPSBlob(nullptr)
		, mVS(nullptr)
		, mHS(nullptr)
		, mDS(nullptr)
		, mGS(nullptr)
		, mPS(nullptr)
	{		
		CreateVSShader(vsFileName, vsFunName);
		CreatePSShader(psFileName, psFunName);
	}

	Shader::~Shader()
	{
	}

	void Shader::createShader(const eShaderType sType, const std::wstring& version,
		const std::wstring& fileName, const std::wstring& funName)
	{
		const HWND hWnd = Engine::GetInst()->GetHwnd();
		const std::string strFunName(String::WStrToStr(funName));
		const std::string strVersion(String::WStrToStr(version));		

		std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
		shaderPath += L"\\Shader\\";
		shaderPath += fileName;

		Microsoft::WRL::ComPtr<ID3DBlob> errBlob;


		if (FAILED(D3DCompileFromFile(shaderPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE,
			strFunName.c_str(), strVersion.c_str(), 0, 0, mVSBlob.GetAddressOf(), errBlob.GetAddressOf())))
		{
			MessageBox(hWnd, L"Failed to compile shader", L"Error", MB_OK);
			return;
		}


		switch (sType)
		{
		case eShaderType::VS:
			if (FAILED(Engine::GetInst()->GetDevice()->CreateVertexShader(mVSBlob->GetBufferPointer(),
				mVSBlob->GetBufferSize(), nullptr, mVS.GetAddressOf())))
			{
				MessageBox(hWnd, L"Failed to create vertex shader", L"Error", MB_OK);
				return;
			}

			break;
		case eShaderType::HS:
			break;
		case eShaderType::DS:
			break;
		case eShaderType::GS:
			break;
		case eShaderType::PS:
			if (FAILED(Engine::GetInst()->GetDevice()->CreatePixelShader(mPSBlob->GetBufferPointer(),
				mPSBlob->GetBufferSize(), nullptr, mPS.GetAddressOf())))
			{
				MessageBox(hWnd, L"Failed to create pixel shader", L"Error", MB_OK);
				return;
			}

			break;
		default:
			break;
		}

	}

	inline void Shader::CreateVSShader(const std::wstring& vsFileName, const std::wstring& vsFunName)
	{
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

	inline void Shader::CreatePSShader(const std::wstring& psFileName, const std::wstring& psFunName)
	{
		createShader(eShaderType::PS, L"ps_5_0", psFileName, psFunName);
	}

	HRESULT Shader::Load(const std::wstring& path)
	{
		(void)path;
		return E_NOTIMPL;
	}
}
