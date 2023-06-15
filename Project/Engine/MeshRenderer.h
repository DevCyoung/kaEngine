#pragma once
#include "Component.h"

namespace engine
{
	enum class eMeshType;
	enum class eShaderType;

	class MeshRenderer : public Component
	{
	public:
		MeshRenderer();
		virtual ~MeshRenderer();
		MeshRenderer(const MeshRenderer&) = delete;
		MeshRenderer& operator=(const MeshRenderer&) = delete;

	public:
		void SetMeshType(const eMeshType type) { mMeshType = type; }
		void SetShaderType(const eShaderType type) { mShaderType = type; }

	private:
		virtual void initialize() override final;
		virtual void update() override final;
		virtual void lateUpdate() override final;
		virtual void render() override final;
	
	private:
		eMeshType mMeshType;
		eShaderType mShaderType;
	};
}