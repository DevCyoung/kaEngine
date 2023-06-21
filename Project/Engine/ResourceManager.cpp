#include "pch.h"
#include "ResourceManager.h"
#include "Engine.h"
#include "GraphicDeviceDx11.h"
#include "StructVertex.h"
#include "Mesh.h"


namespace engine
{
	ResourceManager::ResourceManager()
	{
	}

	ResourceManager::~ResourceManager()
	{
		for (HashMap& item : mResources)
		{
			memory::safe::DeleteUnorderedMap(item);
		}
	}

	void ResourceManager::initialize()
	{
		assert(!sInstance);
		sInstance = new ResourceManager();
		{
			//RectMesh
			const UINT VERTEX_COUNT = 6;

			D3D11_BUFFER_DESC triangleDesc = {};
			triangleDesc.Usage = D3D11_USAGE::D3D11_USAGE_DYNAMIC;
			triangleDesc.ByteWidth = sizeof(tVertex) * VERTEX_COUNT;
			triangleDesc.BindFlags = D3D11_BIND_FLAG::D3D11_BIND_VERTEX_BUFFER;
			triangleDesc.CPUAccessFlags = D3D11_CPU_ACCESS_FLAG::D3D11_CPU_ACCESS_WRITE;

			D3D11_SUBRESOURCE_DATA triangleData = {};
			tVertex vertex[VERTEX_COUNT] = {};

			vertex[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
			vertex[0].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
			vertex[0].uv = Vector2(0.0f, 0.0f);

			vertex[1].pos = Vector3(0.5f, -0.5f, 0.0f);
			vertex[1].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
			vertex[1].uv = Vector2(1.0f, 1.0f);

			vertex[2].pos = Vector3(-0.5f, -0.5f, 0.0f);
			vertex[2].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
			vertex[2].uv = Vector2(0.0f, 1.0f);

			vertex[3].pos = Vector3(-0.5f, 0.5f, 0.0f);
			vertex[3].color = Vector4(1.0f, 0.0f, 0.0f, 1.0f);
			vertex[3].uv = Vector2(0.0f, 0.0f);

			vertex[4].pos = Vector3(0.5f, 0.5f, 0.0f);
			vertex[4].color = Vector4(0.0f, 0.0f, 1.0f, 1.0f);
			vertex[4].uv = Vector2(1.0f, 0.0f);

			vertex[5].pos = Vector3(0.5f, -0.5f, 0.0f);
			vertex[5].color = Vector4(0.0f, 1.0f, 0.0f, 1.0f);
			vertex[5].uv = Vector2(1.0f, 1.0f);

			triangleData.pSysMem = vertex;

			gResourceManager->Insert<Mesh>(L"Rect", new Mesh(triangleDesc, &triangleData,
				sizeof(tVertex), VERTEX_COUNT, gEngine->GetGraphicDevice()->UnSafe_GetDevice()));
		}
	}
}