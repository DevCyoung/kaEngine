#pragma once
#include "Engine.h"
#include "GraphicDeviceDx11.h"

namespace engine
{

//#define DEVICE Engine::GetInst()->GetDevice()
//#define CONTEXT Engine::GetInst()->GetContext()

    struct Vertex
    {
        Vector3 pos;
        Vector4 color;
    };

    class Renderer
    {
    public:
        Renderer();
        ~Renderer();

        void Initialize();        

    private:        
        Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;
        Microsoft::WRL::ComPtr<ID3D11Buffer> mVertexBuffer;
        Microsoft::WRL::ComPtr<ID3DBlob> mErrorBlob;

        Microsoft::WRL::ComPtr<ID3DBlob> mVertexShaderBlob;        
        Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;
        Microsoft::WRL::ComPtr<ID3DBlob> mPixelShaderBlob;
        Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;
    };
}