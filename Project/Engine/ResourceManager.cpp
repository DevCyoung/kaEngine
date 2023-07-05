#include "pch.h"
#include "ResourceManager.h"
#include "Engine.h"
#include "Mesh.h"
#include "Shader.h"

ResourceManager::ResourceManager()
{
	//RectMesh
	{
		constexpr UINT VERTEX_COUNT = 4;
		tVertex vertexs[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2
		vertexs[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexs[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexs[0].uv = Vector2(0.0f, 0.0f);

		vertexs[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexs[1].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexs[1].uv = Vector2(1.0f, 0.0f);

		vertexs[2].pos = Vector3(+0.5f, -0.5f, 0.0f);
		vertexs[2].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexs[2].uv = Vector2(1.0f, 1.0f);

		vertexs[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexs[3].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexs[3].uv = Vector2(0.0f, 1.0f);

		std::vector<UINT> indexes;
		indexes.reserve(10);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		Insert(L"Rect",
			new Mesh(vertexs, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

	//L"\\Shader\\PixelDebug.hlsl",


	//Debug Shader
	{
		Shader* const debugShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VertexShader.hlsl", L"main",
				L"\\Shader\\PixelDebug.hlsl", L"main",
				eRSType::WireframeNone,
				eDSType::None,
				eBSType::Default);
		Insert(L"Debug", debugShader);
	}

}

ResourceManager::~ResourceManager()
{
	for (Dictionary& item : mResources)
	{
		memory::safe::DeleteUnorderedMap(item);
	}
}
