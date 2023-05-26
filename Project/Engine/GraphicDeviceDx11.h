#pragma once
#include "Engine.h"
#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

namespace engine::graphics
{
    class GraphicDeviceDX11
    {
        friend class Engine;

    public:
        GraphicDeviceDX11();
        virtual ~GraphicDeviceDX11();

    private:
        //HRESULT CreateSwapChain(const HWND hWnd, const DXGI_SWAP_CHAIN_DESC& desc);
        //HRESULT CreateTexture(const D3D11_TEXTURE2D_DESC& desc, const void* const data);

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