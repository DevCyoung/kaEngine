#pragma once
#include "Resource.h"

namespace graphics
{
	class GraphicDeviceDX11;
}

namespace engine
{
	class Shader;
	class Texture;

	class Material : public Resource
	{
		friend class MeshRenderer;
		friend class ResourceManager;
		friend class graphics::GraphicDeviceDX11;

	private:
		Material();
		virtual ~Material();
		Material(const Material&) = delete;
		Material& operator=(const Material&) = delete;
	public:
		void SetShader(Shader* const shader) { assert(shader);     mShader = shader; }
		void SetTexture(Texture* const texture) { assert(texture); mTexture = texture; }
		virtual HRESULT Load(const std::wstring& path) override final;

	private:
		Shader* mShader;
		Texture* mTexture;
	};
}