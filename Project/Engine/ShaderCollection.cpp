#include "pch.h"
#include "ShaderCollection.h"

namespace engine
{
	ShaderCollection::ShaderCollection(ID3D11Device* device)
		: mShaders
		{
			Shader(L"VertexShader.hlsl", L"main", L"PixelShader.hlsl", L"main", device),
		}
	{		
	}

	ShaderCollection::~ShaderCollection()
	{
	}
}