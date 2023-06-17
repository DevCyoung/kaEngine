#pragma once

#include "Mesh.h"

namespace engine
{
	enum class eMeshType
	{
		Rect,
		Circle,
		FillRect,
		FillCircle,
		End,
	};

	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
		Vector2 uv;
	};

	class MeshCollection
	{
		friend class graphics::GraphicDeviceDX11;

	private:		
		MeshCollection(ID3D11Device* const device);
		virtual ~MeshCollection();
		MeshCollection(const MeshCollection&) = delete;
		MeshCollection& operator=(const MeshCollection&) = delete;

		void CreateEngineMesh(ID3D11Device* const device);

		Mesh* GetConstantBuffer(const eMeshType type)
		{
			assert(mMeshs[type]);

			return mMeshs[type];
		}

	private:
		std::unordered_map<eMeshType, Mesh*> mMeshs;
	};
}