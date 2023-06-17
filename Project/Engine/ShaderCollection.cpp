#include "pch.h"
#include "ShaderCollection.h"
#include "EnumResourceTypeShader.h"

namespace engine
{
	ShaderCollection::ShaderCollection(ID3D11Device* const device, const HWND hWnd)
		: mShaders
		{
			Shader(eResShader::Default_VertexShader, L"main", eResShader::Default_PixelShader, L"main", device, hWnd),
		}
	{
	}

	ShaderCollection::~ShaderCollection()
	{
	}
}