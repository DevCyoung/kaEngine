#pragma once
#include "Component.h"

class Mesh;
class Material;
class Texture;
class Camera;
class RenderTargetRenderer;

class RenderComponent : public Component
{
	friend class RenderTargetRenderer;
protected:
	RenderComponent(const eComponentType type);
	virtual ~RenderComponent();
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;

public:
	void SetMesh(Mesh* const mesh) { Assert(mesh, WCHAR_IS_NULLPTR); mMesh = mesh; }
	void SetMaterial(Material* const material) { Assert(material, WCHAR_IS_NULLPTR); mMaterial = material; }
	void SetRenderTargetRenderer(RenderTargetRenderer* const renderTargetRenderer) 
	{ 
		Assert(renderTargetRenderer, WCHAR_IS_NULLPTR);
		Assert(!mRenderTargetRenderer, WCHAR_IS_NOT_NULLPTR);

		mRenderTargetRenderer = renderTargetRenderer; 
	}
	Mesh* GetMesh() const { Assert(mMesh, WCHAR_IS_NULLPTR); return mMesh; }
	Material* GetMaterial() const { Assert(mMaterial, WCHAR_IS_NULLPTR); return mMaterial; }

protected:
	virtual void update() override;

private:
	virtual void initialize() override;	
	virtual void lateUpdate() override;
	virtual void render(const Camera* const camera) = 0;
	RenderTargetRenderer* mRenderTargetRenderer;

protected:
	
	Mesh* mMesh; 
	Material* mMaterial;
};
