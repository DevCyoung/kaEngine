#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>

class Engine;
class Shader;
class Texture;

namespace engine::graphics
{
    class GraphicDeviceDX11
    {
        friend class Engine;            
    public:
        GraphicDeviceDX11();
        virtual ~GraphicDeviceDX11();

    private:
        void BindClear();
        void BindConstantBuffer();

        void BindRenderTarget(const Texture& texture);
        void BindPixelShader(const Shader& pixelShader);
        void BindVertexShader(const Shader& vertexShader);
        

    public:
        void Draw();
    private:
        Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> mContext;

        Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTargetTexture;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

        Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilTexture;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;        

        Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
        Microsoft::WRL::ComPtr<ID3D11InputLayout> mInputLayout;


        Microsoft::WRL::ComPtr<ID3DBlob> mErrorBlob;

        Microsoft::WRL::ComPtr<ID3DBlob> mVertexBlob;
        Microsoft::WRL::ComPtr<ID3D11VertexShader> mVertexShader;

        Microsoft::WRL::ComPtr<ID3DBlob> mPixelBlob;
        Microsoft::WRL::ComPtr<ID3D11PixelShader> mPixelShader;

        Microsoft::WRL::ComPtr<ID3D11Buffer> triangleBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer> rectBuffer;

        Microsoft::WRL::ComPtr<ID3D11Buffer> shapeBuffers[1000];
    };
}