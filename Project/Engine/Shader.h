#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>

#include "Resource.h"



namespace engine
{	
	namespace graphics
	{
		class GraphicDeviceDX11;
	}

	enum class eShaderBindType
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
		friend class ShaderCollection;

	public:
		Shader(const std::wstring& vsFileName, const std::wstring& vsFunName,
			const std::wstring& psFileName, const std::wstring psFunName, ID3D11Device* const device);
		Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
			const std::wstring& vsFileName, const std::wstring& vsFunName,
			const std::wstring& psFileName, const std::wstring psFunName, ID3D11Device* const device);
		virtual ~Shader();
		inline void CreateHSShader(const std::wstring& hsFileName, const std::wstring& hsFunName, ID3D11Device* const device);
		inline void CreateDSShader(const std::wstring& dsFileName, const std::wstring& dsFunName, ID3D11Device* const device);
		inline void CreateGSShader(const std::wstring& gsFileName, const std::wstring& gsFunName, ID3D11Device* const device);
		

	private:
		Shader(const Shader&) = delete;
		inline void createVSShader(const std::wstring& vsFileName, const std::wstring& vsFunName, ID3D11Device* const device);
		inline void createPSShader(const std::wstring& psFileName, const std::wstring& psFunName, ID3D11Device* const device);
		void createShader(const eShaderBindType sType, const std::wstring& version,
			const std::wstring& fileName, const std::wstring& funName, ID3D11Device* const device);
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