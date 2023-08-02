#pragma once
#include "Resource.h"
#include <d3d11.h>
#include <d3dcompiler.h>

class ComputeShader : public Resource
{
    friend class GraphicDeviceDX11;
    friend class ResourceManager;

public:	
    ComputeShader() = default;
	ComputeShader(const std::wstring& CSRelativePath, const std::wstring& CSFunName);
	virtual ~ComputeShader();
	ComputeShader(const ComputeShader&) = delete;
	ComputeShader& operator=(const ComputeShader&) = delete;

    void Execute();


private:
    Microsoft::WRL::ComPtr<ID3D11ComputeShader>     mCS;
    Microsoft::WRL::ComPtr<ID3DBlob>                mCSBlob;

protected:
    // 쉐이더에 전달할 상수 데이터
    //tMtrlConst                      m_Const;

    // 그룹 개수
    UINT                            mGroupX;
    UINT                            mGroupY;
    UINT                            mGroupZ;

    // 그룹 1개당 스레드 개수
    UINT                            m_iGroupPerThreadX;
    UINT                            m_iGroupPerThreadY;
    UINT                            m_iGroupPerThreadZ;


    // Resource을(를) 통해 상속됨
    virtual HRESULT Load(const std::wstring& filePath) override;

};