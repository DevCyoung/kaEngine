#pragma once
#include <d3d11.h>
#include <d3dcompiler.h>
#include "Resource.h"
#include "DSCollection.h"
#include "RSCollection.h"
#include "BSCollection.h"

enum class eResShader;

enum class eShaderBindType
{
	VS, HS, DS, GS, PS, CS, End
};

class	Shader : public Resource
{
	friend class GraphicDeviceDX11;
public:
	Shader(const eResShader vsFileName,
		const std::wstring& vsFunName,
		const eResShader psFileName,
		const std::wstring psFunName,
		const eRSType RSType, const eDSType DSType, const eBSType BSType);

	Shader(const D3D11_PRIMITIVE_TOPOLOGY topology,
		const eResShader vsFileName,
		const std::wstring& vsFunName,
		const eResShader psFileName,
		const std::wstring psFunName,
		const eRSType RSType, const eDSType DSType, const eBSType BSType);

public:
	Shader(const D3D11_PRIMITIVE_TOPOLOGY TOPOLOGY,
		const std::wstring& VS_RELATIVE_PATH,
		const std::wstring& VS_FUN_NAME,
		const std::wstring& PS_RELATIVE_PATH,
		const std::wstring& PS_FUN_NAME,
		const eRSType RSType, const eDSType DSType, const eBSType BSType);

	virtual ~Shader();
	Shader(const Shader&) = delete;
	Shader& operator=(const Shader&) = delete;

	void CreateHSShader(const eResShader hsFileName,
		const std::wstring& hsFunName);

	void CreateDSShader(const eResShader dsFileName,
		const std::wstring& dsFunName);

	void CreateGSShader(const eResShader gsFileName,
		const std::wstring& gsFunName);

	eRSType GetRSType() const  { return mRSType;  };
	eDSType GetDSType() const  { return mDSType;  };
	eBSType GetBSType() const  { return mBSType;  };

private:
	void createShader(const eShaderBindType sType,
		const std::wstring& version,
		const eResShader fileName,
		const std::wstring& funName);

	void createShader(const eShaderBindType sType,
		const std::wstring& VERSION,
		const std::wstring& RELATIVE_PATH,
		const std::wstring& FUN_NAME);


	void createVSShader(const std::wstring& VS_RELATIVE_PATH,
		const std::wstring& VS_FUN_NAME);

	void createPSShader(const std::wstring& PS_RELATIVE_PATH,
		const std::wstring& PS_FUN_NAME);

	void createVSShader(const eResShader vsFileName,
		const std::wstring& vsFunName);

	void createPSShader(const eResShader psFileName,
		const std::wstring& psFunName);

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
