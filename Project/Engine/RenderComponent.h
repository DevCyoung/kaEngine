#pragma once
#include "Component.h"

class Mesh;
class Material;
class Camera;

class RenderComponent : public Component
{
	friend class RenderTargetRenderer;

protected:
	RenderComponent(const eComponentType componentType);
	virtual ~RenderComponent();
	RenderComponent(const RenderComponent&) = delete;
	RenderComponent& operator=(const RenderComponent&) = delete;

public:
	Mesh* GetMesh() const { Assert(mMesh, WCHAR_IS_NULLPTR); return mMesh; }
	Material* GetMaterial() const { Assert(mMaterial, WCHAR_IS_NULLPTR); return mMaterial; }

	void SetMesh(Mesh* const mesh) { Assert(mesh, WCHAR_IS_NULLPTR); mMesh = mesh; }
	void SetMaterial(Material* const material) { Assert(material, WCHAR_IS_NULLPTR); mMaterial = material; }

protected:
	virtual void update() override;

private:
	virtual void initialize() override;	
	virtual void lateUpdate() override;
	virtual void render(const Camera* const camera) = 0;

protected:	
	Mesh* mMesh; 
	Material* mMaterial;
};
