#include "pch.h"
#include "MeshCollection.h"

namespace engine
{
	MeshCollection::MeshCollection(ID3D11Device* const device)		
	{				
		CreateEngineMesh(device);
	}

	MeshCollection::~MeshCollection()
	{
		safe::DeleteUnorderedMap(mMeshs);		
	}

	void MeshCollection::CreateEngineMesh(ID3D11Device* const device)
	{
		//RectMesh
		{
			const UINT VERTEX_COUNT = 6;

			D3D11_BUFFER_DESC triangleDesc = {};
			triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
			triangleDesc.ByteWidth = sizeof(Vertex) * 6;
			triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
			triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

			D3D11_SUBRESOURCE_DATA triangleData = {};
			Vertex triVertexes[VERTEX_COUNT] = {};

			triVertexes[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
			triVertexes[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

			triVertexes[1].pos = Vector3(0.5f, -0.5f, 0.0f);
			triVertexes[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

			triVertexes[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
			triVertexes[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

			triVertexes[3].pos = Vector3(-0.5f, 0.5f, 0.0f);
			triVertexes[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);

			triVertexes[4].pos = Vector3(0.5f, 0.5f, 0.0f);
			triVertexes[4].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);

			triVertexes[5].pos = Vector3(0.5f, -0.5f, 0.0f);
			triVertexes[5].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);

			triangleData.pSysMem = triVertexes;

			mMeshs.insert(std::make_pair(eMeshType::Rect,
				new Mesh(triangleDesc, &triangleData, sizeof(Vertex), VERTEX_COUNT, device)));
		}

	}
}