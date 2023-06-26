#pragma once
#include "Component.h"

class Mesh;
class Material;
class Texture;

class MeshRenderer : public Component
{
public:
	MeshRenderer();
	virtual ~MeshRenderer();
	MeshRenderer(const MeshRenderer&) = delete;
	MeshRenderer& operator=(const MeshRenderer&) = delete;

	void SetMesh(Mesh* const mesh) { Assert(mesh, WCHAR_IS_NULLPTR); mMesh = mesh; }
	void SetMaterial(Material* const material) { Assert(material, WCHAR_IS_NULLPTR); mMaterial = material; }

	Mesh* GetMesh() const { Assert(mMesh, WCHAR_IS_NULLPTR); return mMesh; }
	Material* GetMaterial() const { Assert(mMaterial, WCHAR_IS_NULLPTR); return mMaterial; }


private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;

private:
	Mesh* mMesh;
	Material* mMaterial;
	Texture* mRenderTarget;
};

REGISTER_COMPONENT_TYPE(MeshRenderer);
