#include "GraphicDeviceDX11.h"
#include "Engine.h"

namespace engine::graphics
{
    GraphicDeviceDX11::GraphicDeviceDX11()
    {
        const Engine* const engine = Engine::GetInst();

        const HWND hWnd = engine->GetHwnd();
        const UINT screenWidth = engine->GetScreenWidth();
        const UINT screenHeight = engine->GetScreenHeight();
        const UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;

        //Device
        {
            D3D_FEATURE_LEVEL featureLevel = static_cast<D3D_FEATURE_LEVEL>(0);
            if (FAILED(D3D11CreateDevice(nullptr, D3D_DRIVER_TYPE_HARDWARE, 
                                         nullptr, deviceFlag, nullptr, 0, D3D11_SDK_VERSION,
                                         mDevice.GetAddressOf(), &featureLevel, 
                                         mContext.GetAddressOf())))
            {                
                MessageBox(hWnd, L"Failed to create device", L"Error", MB_OK);
                return;
            }
        }        

        //SwapChain
        {
            DXGI_SWAP_CHAIN_DESC swapChainDesc = {};

            swapChainDesc.BufferCount = 2;  
            swapChainDesc.SampleDesc.Count = 1;
            swapChainDesc.SampleDesc.Quality = 0;

            swapChainDesc.OutputWindow = hWnd;
            swapChainDesc.Windowed = TRUE;
            swapChainDesc.BufferDesc.Width = screenWidth;
            swapChainDesc.BufferDesc.Height = screenHeight;

            swapChainDesc.BufferDesc.RefreshRate.Numerator = 240;   //최대프레임
            swapChainDesc.BufferDesc.RefreshRate.Denominator = 1;   //최소프레임
            swapChainDesc.BufferDesc.Scaling = DXGI_MODE_SCALING_UNSPECIFIED;
            swapChainDesc.BufferDesc.ScanlineOrdering = DXGI_MODE_SCANLINE_ORDER::DXGI_MODE_SCANLINE_ORDER_UNSPECIFIED;

            //OLD? DXGI_SWAP_EFFECT_DISCARD
            swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD;
            
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; //픽셀 포맷                        
            

            if (FAILED(CreateSwapChain(hWnd, swapChainDesc)))
            {
                MessageBox(hWnd, L"Failed to create swap chain", L"Error", MB_OK);
                return;
            }

            //RenderTarget
            if (FAILED(mSwapChain->GetBuffer(0, __uuidof(ID3D11Texture2D), reinterpret_cast<void**>(mRenderTargetTexture.GetAddressOf()))))
            {
                MessageBox(hWnd, L"Failed to get buffer", L"Error", MB_OK);
                return;
            }

            if (FAILED(mDevice->CreateRenderTargetView(mRenderTargetTexture.Get(), nullptr, mRenderTargetView.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to create render target view", L"Error", MB_OK);
                return;
            }
        }

        //DepthStencil
        {
            D3D11_TEXTURE2D_DESC depthStencilDesc = {};

            depthStencilDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_DEPTH_STENCIL;
            depthStencilDesc.Format = DXGI_FORMAT::DXGI_FORMAT_D24_UNORM_S8_UINT;
            depthStencilDesc.Usage = D3D11_USAGE_DEFAULT;
            depthStencilDesc.Width = screenWidth;
            depthStencilDesc.Height = screenHeight;
            depthStencilDesc.ArraySize = 1;
            depthStencilDesc.SampleDesc.Count = 1;
            depthStencilDesc.MiscFlags = 0;
                  

            if (FAILED(mDevice->CreateTexture2D(&depthStencilDesc, nullptr, mDepthStencilTexture.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to create depth stencil texture", L"Error", MB_OK);
                return;
            }

            if (FAILED(mDevice->CreateDepthStencilView(mDepthStencilTexture.Get(), nullptr, mDepthStencilView.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to create depth stencil view", L"Error", MB_OK);
                return;
            } 
        }

        //OM단계 셋팅
        mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
    }

    GraphicDeviceDX11::~GraphicDeviceDX11()
    {
    }

    HRESULT GraphicDeviceDX11::CreateSwapChain(const HWND hWnd, const DXGI_SWAP_CHAIN_DESC& desc)
    {
        DXGI_SWAP_CHAIN_DESC swapChainDesc = desc;

        IDXGIDevice* pDXGIDevice = nullptr;
        IDXGIAdapter* pDXGIAdapter = nullptr;
        IDXGIFactory* pDXGIFactory = nullptr;

        if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pDXGIDevice))))
        {
            return S_FALSE;
        }

        if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pDXGIAdapter))))
        {
            return S_FALSE;
        }

        if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pDXGIFactory))))
        {
            return S_FALSE;
        }

        if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), &swapChainDesc, mSwapChain.GetAddressOf())))
        {
            return S_FALSE;
        }
        pDXGIDevice->Release();
        pDXGIAdapter->Release();
        pDXGIFactory->Release();

        (void)hWnd;

        return S_OK;
    }

    void GraphicDeviceDX11::Draw()
    {
        //검은색 background는 자제할것
        const FLOAT bgColor[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
        mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);

        //Swap backbuffer, frontbuffer
         mSwapChain->Present(0, 0);
    }
}