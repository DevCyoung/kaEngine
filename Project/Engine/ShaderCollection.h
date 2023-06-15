#pragma once

#include "Shader.h"

namespace engine
{
	enum class eShaderType
	{
		Default,
		End,
	};

	class ShaderCollection
	{
		friend class graphics::GraphicDeviceDX11;

	private:
		ShaderCollection(ID3D11Device* device);
		ShaderCollection(const ShaderCollection& other) = delete;
		ShaderCollection& operator =(const ShaderCollection& other) = delete;
		virtual ~ShaderCollection();

		Shader& GetShader(const eShaderType type)
		{
			return mShaders[static_cast<UINT>(type)];
		}

	private:
		Shader mShaders[static_cast<UINT>(eShaderType::End)];
	};
}