#pragma once
#include "Resource.h"
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Engine.h"
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

	class	Shader : public Resource
	{
		friend class graphics::GraphicDeviceDX11;

	public:
		Shader(const std::wstring& vsFileName, const std::wstring& vsFunName,
			const std::wstring& psFileName, const std::wstring psFunName);
		Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
			const std::wstring& vsFileName, const std::wstring& vsFunName,
			const std::wstring& psFileName, const std::wstring psFunName);
		virtual ~Shader();
		inline void CreateHSShader(const std::wstring& hsFileName, const std::wstring& hsFunName);
		inline void CreateDSShader(const std::wstring& dsFileName, const std::wstring& dsFunName);
		inline void CreateGSShader(const std::wstring& gsFileName, const std::wstring& gsFunName);
		

	private:
		Shader(const Shader&) = delete;
		inline void createVSShader(const std::wstring& vsFileName, const std::wstring& vsFunName);
		inline void createPSShader(const std::wstring& psFileName, const std::wstring& psFunName);
		void createShader(const eShaderType sType, const std::wstring& version, 
			const std::wstring& fileName, const std::wstring& funName);	
	virtual HRESULT Load(const std::wstring& path) override;

	private:
		D3D11_PRIMITIVE_TOPOLOGY mTopology;
		Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;

		Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
		Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
		Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
		Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
		Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;
	};
}