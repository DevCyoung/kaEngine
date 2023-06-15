#pragma once
#include "Shader.h"

namespace engine
{
	enum class eShaderType
	{
		Default,
		Animation,
		Shadow,
		Blink,
		Blood,
		End,
	};

	class ShaderCollection
	{
		friend class graphics::GraphicDeviceDX11;

	private:
		ShaderCollection(ID3D11Device* const device, const HWND hWnd);
		virtual ~ShaderCollection();
		ShaderCollection(const ShaderCollection&) = delete;
		ShaderCollection& operator=(const ShaderCollection&) = delete;

		Shader& GetShader(const eShaderType type)
		{
			return mShaders[static_cast<UINT>(type)];
		}

	private:
		Shader mShaders[static_cast<UINT>(eShaderType::End)];
	};
}