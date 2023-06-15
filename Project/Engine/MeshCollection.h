#pragma once
#include "Mesh.h"

namespace engine
{
	enum class eVBType
	{
		Rect,
		Circle,
		End,
	};

	struct Vertex
	{
		Vector3 pos;
		Vector4 color;
	};

	class MeshCollection
	{
		friend class graphics::GraphicDeviceDX11;

	private:		
		MeshCollection(ID3D11Device* const device);
		virtual ~MeshCollection();
		MeshCollection(const MeshCollection& other) = delete;
		MeshCollection& operator =(const MeshCollection& other) = delete;

		void CreateEngineMesh(ID3D11Device* const device);

		Mesh* GetConstantBuffer(const eVBType type) 
		{
			return mMeshs[type];
		}

	private:
		std::unordered_map<eVBType, Mesh*> mMeshs;
	};
}