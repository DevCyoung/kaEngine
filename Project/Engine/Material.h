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

	public:
		Material();
		virtual ~Material();
		Material(const Material&) = delete;
		Material& operator=(const Material&) = delete;

	public:
		void SetShader(Shader* const shader) { Assert(shader, WCHAR_IS_NULLPTR); mShader = shader; }
		void SetTexture(Texture* const texture) { Assert(texture, WCHAR_IS_NULLPTR); mTexture = texture; }
		virtual HRESULT Load(const std::wstring& path) override final;

	private:
		Shader* mShader;
		Texture* mTexture;
	};
}