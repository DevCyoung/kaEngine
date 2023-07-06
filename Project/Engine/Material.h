#pragma once
#include "Resource.h"
#include "EnumRenderType.h"

class Shader;
class Texture;

class Material : public Resource
{	
	friend class GraphicDeviceDX11;
public:
	Material(const eRenderPriorityType RENDER_PRIORITY_TYPE);
	virtual ~Material();
	Material(const Material&) = delete;
	Material& operator=(const Material&) = delete;

public:
	const Texture*  GetTexture() const { Assert(mTexture, WCHAR_IS_NULLPTR); return mTexture; }
	const Shader* GetShader() const { Assert(mShader, WCHAR_IS_NULLPTR); return mShader; }
	eRenderPriorityType GetRenderType() const { return mRenderType; }

	void SetShader(Shader* const shader) { Assert(shader, WCHAR_IS_NULLPTR); mShader = shader; }
	void SetTexture(Texture* const texture) { Assert(texture, WCHAR_IS_NULLPTR); mTexture = texture; }

	virtual HRESULT Load(const std::wstring& FULL_PATH) override final;

private:
	Shader* mShader;
	Texture* mTexture;
	eRenderPriorityType mRenderType;
};
