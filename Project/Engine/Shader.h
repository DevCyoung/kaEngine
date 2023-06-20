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
		VS, HS, DS, GS, PS, CS
	};

	enum class eResShader;

	class	Shader : public Resource
	{
		friend class graphics::GraphicDeviceDX11;		

	public:
		Shader(const eResShader vsFileName,
			const std::wstring& vsFunName,
			const eResShader psFileName,
			const std::wstring psFunName, 
			ID3D11Device* const device, 
			const HWND hwnd);

		Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
			const eResShader vsFileName,
			const std::wstring& vsFunName,
			const eResShader psFileName,
			const std::wstring psFunName, 
			ID3D11Device* const device, 
			const HWND hwnd);

		virtual ~Shader();
		Shader(const Shader&) = delete;
		Shader& operator=(const Shader&) = delete;

		void CreateHSShader(const eResShader hsFileName,
			const std::wstring& hsFunName, 
			ID3D11Device* const device, 
			const HWND hwnd);

		void CreateDSShader(const eResShader dsFileName,
			const std::wstring& dsFunName, 
			ID3D11Device* const device,
			const HWND hwnd);

		void CreateGSShader(const eResShader gsFileName,
			const std::wstring& gsFunName, 
			ID3D11Device* const device,
			const HWND hwnd);		

	private:		
		void createShader(const eShaderBindType sType,
			const std::wstring& version,
			const eResShader fileName,
			const std::wstring& funName,
			ID3D11Device* const device,
			const HWND hwnd);

		void createVSShader(const eResShader vsFileName,
			const std::wstring& vsFunName,
			ID3D11Device* const device,
			const HWND hwnd);

		void createPSShader(const eResShader psFileName,
			const std::wstring& psFunName, 
			ID3D11Device* const device, 
			const HWND hwnd);

		
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