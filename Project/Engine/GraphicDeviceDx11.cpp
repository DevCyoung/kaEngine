#include "GraphicDeviceDX11.h"
#include "Engine.h"

#pragma comment(lib, "d3d11.lib")
#pragma comment(lib, "d3dcompiler.lib")

/*
* Trouble : Fxing
* Date : 2023-05-26
* Author : yoseo
* 현재 SwapChain생성중 Warning 발생
* DXGI WARNING: IDXGIFactory::CreateSwapChain: Blt-model swap effects (DXGI_SWAP_EFFECT_DISCARD and DXGI_SWAP_EFFECT_SEQUENTIAL) are legacy swap effects that are predominantly superceded by their flip-model counterparts (DXGI_SWAP_EFFECT_FLIP_SEQUENTIAL and DXGI_SWAP_EFFECT_FLIP_DISCARD). Please consider updating your application to leverage flip-model swap effects to benefit from modern presentation enhancements. More information is available at http://aka.ms/dxgiflipmodel. [ MISCELLANEOUS WARNING #294: ]*
* DXGI_SWAP_CHAIN_DESC 구조체의 swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
* 부분을 DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_FLIP_DISCARD 으로 교체하면 Warning은 사라지지만 프레임이 60으로 고정
* 되거나 혹은 떨어지는 현상이 발생한다.
* 해결하려고 시도중입니다.
* Date : 2023-05-29
* 아직진행중...
*/

namespace engine::graphics
{
    struct Vertex
    {
        Vector3 pos;
        Vector4 color;
    };
    
#define SHAPE_COUNT 45

    GraphicDeviceDX11::GraphicDeviceDX11()
    {
        
        const Engine* const engine = Engine::GetInst();

        const HWND hWnd = engine->GetHwnd();
        const UINT screenWidth = engine->GetScreenWidth();
        const UINT screenHeight = engine->GetScreenHeight();

#ifdef _DEBUG
        const UINT deviceFlag = D3D11_CREATE_DEVICE_DEBUG;
#else
        const UINT deviceFlag = D3D11_CREATE_DEVICE_SINGLETHREADED;
#endif

        

        //Create Device
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

        //Buffer
        {
            D3D11_BUFFER_DESC triangleDesc = {};
            triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
            triangleDesc.ByteWidth = sizeof(Vertex) * 6;
            triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
            triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

            D3D11_SUBRESOURCE_DATA triangleData = {};
            Vertex triVertexes[6] = {};            
            
            Microsoft::WRL::ComPtr<IUnknown> ptr;                        

            //mContext->OMSetRenderTargets()         

            triVertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
            triVertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

            triVertexes[1].pos = Vector3(0.5f,  -0.5f, 0.0f);
            triVertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

            triVertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
            triVertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);


            triVertexes[3].pos   = Vector3(-0.5f, 0.5f, 0.0f);
            triVertexes[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

            triVertexes[4].pos = Vector3(0.5f, 0.5f, 0.0f);
            triVertexes[4].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

            triVertexes[5].pos = Vector3(0.5f, -0.5f, 0.0f);
            triVertexes[5].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);


            triangleData.pSysMem = triVertexes;
            if (FAILED(mDevice->CreateBuffer(&triangleDesc, &triangleData, triangleBuffer.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to create triangle buffer", L"Error", MB_OK);
                return;
            }

            //RectBuffer
            constexpr UINT rectDataCount = 4;
            D3D11_BUFFER_DESC rectDesc = {};
            rectDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
            rectDesc.ByteWidth = sizeof(Vertex) * rectDataCount;
            rectDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
            rectDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

            D3D11_SUBRESOURCE_DATA rectData = {};
            Vertex rectVertexes[rectDataCount] = {};
            
            rectVertexes[0].pos   = Vector3(-0.5f, 0.5f, 0.0f);
            rectVertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

            rectVertexes[1].pos   = Vector3(0.5f, 0.5f, 0.0f);
            rectVertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

            rectVertexes[2].pos   = Vector3(0.5f, -0.5f, 0.0f);
            rectVertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

            rectVertexes[3].pos   = Vector3(-0.5f, -0.5f, 0.0f);
            rectVertexes[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);


            rectData.pSysMem = rectVertexes;
            if (FAILED(mDevice->CreateBuffer(&rectDesc, &rectData, rectBuffer.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to create triangle buffer", L"Error", MB_OK);
                return;
            }





            const float PI = 3.141592f;
            const UINT shapeCount[4] = { 4, 5, 6};

            float yde =  0.77f;
            float xde = -0.89f;

            for (UINT i = 0; i <= SHAPE_COUNT; ++i)
            {
                D3D11_BUFFER_DESC shapeDesc = {};
                shapeDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
                shapeDesc.ByteWidth = sizeof(Vertex) * (i + 4) * 3 ;
                shapeDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
                shapeDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

                D3D11_SUBRESOURCE_DATA shapeData = {};

                Vector3 shapePoints[1000];
                Vertex shapeVertexes[1000];

                if (i % 9 == 0 && i != 0)
                {
                    yde  -= 0.37f;
                    xde   = -0.89f;
                }

                



                const float perRadin = (float)(2 * PI) / (float)(i + 4);

                shapePoints[0] = Vector3(0.0f, 0.0f, 0.0f);


                //길이정규화
                    float ratio = (float)Engine::GetInst()->GetScreenHeight() / (float)Engine::GetInst()->GetScreenWidth();
                for (UINT j = 1; j <= (i + 5); ++j)
                {                    
                    float radin = perRadin * (j - 1);
                    float angle = radin * 180.0f / PI;
                    (void)angle;

                    
                    (void)ratio;
                    //Engine::GetInst()->GetScreenWidth();
                    //Engine::GetInst()->GetScreenHeight();


                    float x = cosf(radin) * ratio * 0.15f; // -1 ~ 1
                    float y = sinf(radin) * 0.15f; // -1 ~ 1
                    
                    shapePoints[j] = Vector3(x, y, 0.0f);
                }

                
                for (UINT j = 0; j < (i + 4); ++j)
                {
                    shapeVertexes[j * 3 + 0].pos = shapePoints[j + 2];
                    shapeVertexes[j * 3 + 0].pos += Vector3(xde, yde, 0.0f);

                    shapeVertexes[j * 3 + 1].pos = shapePoints[j+ 1];
                    shapeVertexes[j * 3 + 1].pos += Vector3(xde, yde, 0.0f);

                    shapeVertexes[j * 3 + 2].pos = shapePoints[0]    ;
                    shapeVertexes[j * 3 + 2].pos += Vector3(xde, yde, 0.0f);

                    shapeVertexes[j * 3 + 0].color = Vector4(0.f, 0.f, 0.0f, 1.f);
                    shapeVertexes[j * 3 + 1].color = Vector4(j * 0.05f, 1.0f, 0.0f, 1.f);
                    shapeVertexes[j * 3 + 2].color = Vector4(j * 0.05f, 1.0f, 0.0f, 1.f);                   
                }

                shapeData.pSysMem = shapeVertexes;
                if (FAILED(mDevice->CreateBuffer(&shapeDesc, &shapeData, shapeBuffers[i].GetAddressOf())))
                {
                    MessageBox(hWnd, L"Failed to create triangle buffer", L"Error", MB_OK);
                    return;
                }

                xde += 0.22f;
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

            swapChainDesc.SwapEffect = DXGI_SWAP_EFFECT::DXGI_SWAP_EFFECT_DISCARD;
            swapChainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
            swapChainDesc.BufferDesc.Format = DXGI_FORMAT::DXGI_FORMAT_R8G8B8A8_UNORM; //픽셀 포맷                                    

            IDXGIDevice* pDXGIDevice = nullptr;
            IDXGIAdapter* pDXGIAdapter = nullptr;
            IDXGIFactory* pDXGIFactory = nullptr;

            if (FAILED(mDevice->QueryInterface(__uuidof(IDXGIDevice), reinterpret_cast<void**>(&pDXGIDevice))))
            {
                MessageBox(hWnd, L"Failed to create IDXGIDevice", L"Error", MB_OK);
                return;
            }

            if (FAILED(pDXGIDevice->GetParent(__uuidof(IDXGIAdapter), reinterpret_cast<void**>(&pDXGIAdapter))))
            {
                MessageBox(hWnd, L"Failed to create IDXGIAdapter", L"Error", MB_OK);
                return;
            }

            if (FAILED(pDXGIAdapter->GetParent(__uuidof(IDXGIFactory), reinterpret_cast<void**>(&pDXGIFactory))))
            {
                MessageBox(hWnd, L"Failed to create IDXGIFactory", L"Error", MB_OK);
                return;
            }

            if (FAILED(pDXGIFactory->CreateSwapChain(mDevice.Get(), &swapChainDesc, mSwapChain.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to create IDXGISwapChain", L"Error", MB_OK);
                return;
            }

            pDXGIDevice->Release();
            pDXGIAdapter->Release();
            pDXGIFactory->Release();

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


        //Create shader
        {
            std::filesystem::path shaderPath = std::filesystem::current_path().parent_path();
            shaderPath += L"\\Shader\\";

            std::filesystem::path vsPath(shaderPath);
            vsPath += L"VertexShader.hlsl";


            if (FAILED(D3DCompileFromFile(vsPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "vs_5_0",
                0, 0, mVertexBlob.GetAddressOf(), mErrorBlob.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to compile vertex shader", L"Error", MB_OK);
                return;
            }

            if (FAILED(mDevice->CreateVertexShader(mVertexBlob->GetBufferPointer(), mVertexBlob->GetBufferSize(), nullptr, mVertexShader.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to create vertex shader", L"Error", MB_OK);
                return;
            }

            std::filesystem::path psPath(shaderPath);
            psPath += L"PixelShader.hlsl";

            if (FAILED(D3DCompileFromFile(psPath.c_str(), nullptr, D3D_COMPILE_STANDARD_FILE_INCLUDE, "main", "ps_5_0",
                0, 0, mPixelBlob.GetAddressOf(), mErrorBlob.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to compile pixel shader", L"Error", MB_OK);
                return;
            }

            if (FAILED(mDevice->CreatePixelShader(mPixelBlob->GetBufferPointer(), mPixelBlob->GetBufferSize(), nullptr, mPixelShader.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to create pixel shader", L"Error", MB_OK);
                return;
            }
        }

        //InputLayout
        {
            D3D11_INPUT_ELEMENT_DESC arrLayout[2] = {};

            arrLayout[0].AlignedByteOffset = 0;
            arrLayout[0].Format = DXGI_FORMAT_R32G32B32_FLOAT;
            arrLayout[0].InputSlot = 0;
            arrLayout[0].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            arrLayout[0].SemanticName = "POSITION";
            arrLayout[0].SemanticIndex = 0;

            arrLayout[1].AlignedByteOffset = 12;
            arrLayout[1].Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
            arrLayout[1].InputSlot = 0;
            arrLayout[1].InputSlotClass = D3D11_INPUT_PER_VERTEX_DATA;
            arrLayout[1].SemanticName = "COLOR";
            arrLayout[1].SemanticIndex = 0;

            if (FAILED(mDevice->CreateInputLayout(arrLayout, 2
                , mVertexBlob->GetBufferPointer()
                , mVertexBlob->GetBufferSize()
                , mInputLayout.GetAddressOf())))
            {
                MessageBox(hWnd, L"Failed to create input layout", L"Error", MB_OK);
                return;
            }
        }

        //OM단계 셋팅
        {
            mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());
        }
    }

    GraphicDeviceDX11::~GraphicDeviceDX11()
    {
    }


    void GraphicDeviceDX11::Draw()
    {
        //검은색 background는 자제할것
        const FLOAT bgColor[4] = { 0.4f, 0.4f, 0.4f, 1.0f };
        mContext->ClearRenderTargetView(mRenderTargetView.Get(), bgColor);
        mContext->ClearDepthStencilView(mDepthStencilView.Get(), D3D11_CLEAR_DEPTH | D3D11_CLEAR_STENCIL, 1.0f, 0);

        //IA
        //mContext->IASetVertexBuffers(0, 1, &)
        //        
        const FLOAT scerenWidth = static_cast<FLOAT>(Engine::GetInst()->GetScreenWidth());
        const FLOAT screnHeight = static_cast<FLOAT>(Engine::GetInst()->GetScreenHeight());

        Engine::GetInst()->GetScreenHeight();
        D3D11_VIEWPORT mViewPort =
        {
            0.0f, 0.0f,        
            scerenWidth, screnHeight,
            0.0f, 1.0f
        };
        mContext->RSSetViewports(1, &mViewPort);

        mContext->OMSetRenderTargets(1, mRenderTargetView.GetAddressOf(), mDepthStencilView.Get());


        // input assembler 정점데이터 정보 지정
        UINT vertexsize = sizeof(Vertex);
        UINT offset = 0;

        mContext->IASetInputLayout(mInputLayout.Get());
        mContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);

        //Bind VS, PS 
        mContext->VSSetShader(mVertexShader.Get(), 0, 0);
        mContext->PSSetShader(mPixelShader.Get(), 0, 0);


        for (UINT i = 0; i < SHAPE_COUNT; ++i)
        {
            mContext->IASetVertexBuffers(0, 1, shapeBuffers[i].GetAddressOf(), &vertexsize, &offset);            
            // Draw Render Target
            mContext->Draw(12 + i * 3, 0);
        }
        

        //Swap backbuffer, frontbuffer
        mSwapChain->Present(0, 0);
    }
}