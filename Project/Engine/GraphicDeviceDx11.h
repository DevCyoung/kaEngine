#pragma once

#include <d3d11.h>
#include <d3dcompiler.h>
#include <wrl/client.h>
#include "Shader.h"
#include "ConstantBuffer.h"

class Engine;
class Texture;

namespace engine::graphics
{
    struct tTransform
    {
        Vector4 pos;

    };

    class GraphicDeviceDX11
    {
        friend class Engine;            
    public:
        GraphicDeviceDX11();        
        virtual ~GraphicDeviceDX11();

    private:
        void clearRenderTarget();
        void present();
        //void BindConstantBuffer();

        //void BindRenderTarget(const Texture& texture);
        //void BindPixelShader(const Shader& pixelShader);
        //void BindVertexShader(const Shader& vertexShader);
    public:
        void BindIA(const Shader& shader);
        void BindVS(const Shader& shader);
        void BindPS(const Shader& shader);
        //void BindVB();
        void BindCB(const eShaderStage stage, const ConstantBuffer& CB);

            

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

        Microsoft::WRL::ComPtr<ID3D11Buffer> triangleBuffer;
        Microsoft::WRL::ComPtr<ID3D11Buffer> rectBuffer;

        Microsoft::WRL::ComPtr<ID3D11Buffer> shapeBuffers[1000];

        

        //Shader* mTestShader;
    };
}