#pragma once

#include "Resource.h"

#include <d3d11.h>
#include <d3dcompiler.h>

namespace engine
{	
	enum class eShaderType
	{
		VS,
		HS,
		DS,
		GS,
		PS
	};
	class Shader : public Resource
	{

	private:
		Shader(const D3D11_PRIMITIVE_TOPOLOGY topology, 
			const std::wstring& vsFileName, const std::wstring& vsFunName,
			const std::wstring& psFileName, const std::wstring psFunName);		
		virtual ~Shader();	
	private:
		void createShader(const eShaderType sType, const std::wstring& version, const std::wstring& fileName, const std::wstring& funName);

	public:
		inline void CreateVSShader(const std::wstring& vsFileName, const std::wstring& vsFunName);
		inline void CreateHSShader(const std::wstring& hsFileName, const std::wstring& hsFunName);
		inline void CreateDSShader(const std::wstring& dsFileName, const std::wstring& dsFunName);
		inline void CreateGSShader(const std::wstring& gsFileName, const std::wstring& gsFunName);
		inline void CreatePSShader(const std::wstring& psFileName, const std::wstring& psFunName);

	

	private:
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

		Microsoft::WRL::ComPtr<ID3DBlob> mVSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mHSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mDSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mGSBlob;
		Microsoft::WRL::ComPtr<ID3DBlob> mPSBlob;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;

		// Resource을(를) 통해 상속됨
		virtual HRESULT Load(const std::wstring& path) override;
	};
}