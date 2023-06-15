#include "pch.h"
#include "ShaderCollection.h"

namespace engine
{
	ShaderCollection::ShaderCollection(ID3D11Device* const device, const HWND hWnd)
		: mShaders
		{
			Shader(L"VertexShader.hlsl", L"main", L"PixelShader.hlsl", L"main", device, hWnd),
		}
	{		
	}

	ShaderCollection::~ShaderCollection()
	{
	}
}