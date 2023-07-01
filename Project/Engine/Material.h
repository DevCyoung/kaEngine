#pragma once
#include "Resource.h"
#include "EnumRenderType.h"

class Shader;
class Texture;

class Material : public Resource
{
	friend class MeshRenderer;
	friend class GraphicDeviceDX11;

public:
	Material(const eRenderType type);
	virtual ~Material();
	Material(const Material&) = delete;
	Material& operator=(const Material&) = delete;

public:
	Texture*  GetTexture() const { Assert(mTexture, WCHAR_IS_NULLPTR); return mTexture; }
	eRenderType GetRenderType() const { return mRenderType; }

	void SetShader(Shader* const shader) { Assert(shader, WCHAR_IS_NULLPTR); mShader = shader; }
	void SetTexture(Texture* const texture) { Assert(texture, WCHAR_IS_NULLPTR); mTexture = texture; }

	virtual HRESULT Load(const std::wstring& path) override final;

private:
	Shader* mShader;
	Texture* mTexture;
	eRenderType mRenderType;
};
