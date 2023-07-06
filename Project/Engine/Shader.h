#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "DSCollection.h"
#include "RSCollection.h"
#include "BSCollection.h"
#include "IEDCollection.h"

enum class eResShader;

enum class eShaderBindType
{
	VS, HS, DS, GS, PS, CS, End
};


class	Shader : public Resource
{
	friend class GraphicDeviceDX11;

public:
	Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
		const eResShader VS_RELATIVE_PATH, const std::wstring& VS_FUN_NAME,
		const eResShader PS_RELATIVE_PATH, const std::wstring& PS_FUN_NAME,
		const eIEDType IED_TYPE, const eRSType RS_TYPE, const eDSType DS_TYPE, const eBSType BS_TYPE);

	Shader(const D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY,
		const std::wstring& VS_RELATIVE_PATH, const std::wstring& VS_FUN_NAME ,
		const std::wstring& PS_RELATIVE_PATH, const std::wstring& PS_FUN_NAME ,
		const eIEDType IED_TYPE, const eRSType RS_TYPE, const eDSType DS_TYPE, const eBSType BS_TYPE);

	virtual ~Shader();
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	eRSType GetRSType() const  { return mRSType;  };
	eDSType GetDSType() const  { return mDSType;  };
	eBSType GetBSType() const  { return mBSType;  };

private:
	void createVSShader(const std::wstring& VS_RELATIVE_PATH,
		const std::wstring& VS_FUN_NAME, const eIEDType& IED_TYPE);

	void createPSShader(const std::wstring& PS_RELATIVE_PATH,
		const std::wstring& PS_FUN_NAME);

	void shaderCompile(const std::wstring& RELATIVE_PATH, 
		const std::wstring& FUN_NAME, 
		const std::wstring& VERSION,
		ID3DBlob** const blob,
		ID3DBlob** const errorBlob);


	virtual HRESULT Load(const std::wstring& path) override;

private:
	D3D11_PRIMITIVE_TOPOLOGY mTopology;
	Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
	Microsoft::WRL::ComPtr<ID3D11VertexShader> mVS;
	Microsoft::WRL::ComPtr<ID3D11HullShader> mHS;
	Microsoft::WRL::ComPtr<ID3D11DomainShader> mDS;
	Microsoft::WRL::ComPtr<ID3D11GeometryShader> mGS;
	Microsoft::WRL::ComPtr<ID3D11PixelShader> mPS;

	eRSType mRSType;
	eDSType mDSType;
	eBSType mBSType;
};
