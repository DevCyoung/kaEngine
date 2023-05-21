#pragma once
#include "Engine.h"

#include <d3d11.h>
#include <d3dcompiler.h>

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")



namespace engine::graphics
{
    class GraphicDeviceDx11
    {
    public:
        GraphicDeviceDx11();
        virtual ~GraphicDeviceDx11();

    private:
        Microsoft::WRL::ComPtr<ID3D11Device> mDevice;
        Microsoft::WRL::ComPtr<ID3D11DeviceContext> mDeviceContext;

        Microsoft::WRL::ComPtr<ID3D11Texture2D> mRenderTarget;
        Microsoft::WRL::ComPtr<ID3D11RenderTargetView> mRenderTargetView;

        Microsoft::WRL::ComPtr<ID3D11Texture2D> mDepthStencilBuffer;
        Microsoft::WRL::ComPtr<ID3D11DepthStencilView> mDepthStencilView;
        
        Microsoft::WRL::ComPtr<IDXGISwapChain> mSwapChain;
    };
}
