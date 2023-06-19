#pragma once
#include "Component.h"

namespace engine
{	
	class Mesh;
	class Material;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();
		MeshRenderer(const MeshRenderer&) = delete;
		MeshRenderer& operator=(const MeshRenderer&) = delete;

		void SetMesh(Mesh* const mesh) { assert(mesh); mMesh = mesh; }
		void SetMaterial(Material* const material) { assert(material); mMaterial = material; }

		Mesh* GetMesh() const { assert(mMesh); return mMesh; }
		Material* GetMaterial() const { assert(mMaterial); return mMaterial; }


	private:
		virtual void initialize() override final;
		virtual void update() override final;
		virtual void lateUpdate() override final;
		virtual void render() override final;
	
	private:
		Mesh* mMesh;
		Material* mMaterial;
	};
}