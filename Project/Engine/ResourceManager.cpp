#include "pch.h"
#include "ResourceManager.h"
#include "Engine.h"
#include "Mesh.h"
#include "Shader.h"
#include "StructVertex.h"
#include "EngineMath.h"
ResourceManager::ResourceManager()
{

#pragma region Mesh
	//fill rect mesh
	{
		constexpr UINT VERTEX_COUNT = 4;
		tVertex vertexArray[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2
		vertexArray[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		vertexArray[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexArray[1].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[1].uv = Vector2(1.0f, 0.0f);

		vertexArray[2].pos = Vector3(+0.5f, -0.5f, 0.0f);
		vertexArray[2].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[2].uv = Vector2(1.0f, 1.0f);

		vertexArray[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexArray[3].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[3].uv = Vector2(0.0f, 1.0f);

		std::vector<UINT> indexes;
		indexes.reserve(10);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);

		indexes.push_back(0);
		indexes.push_back(2);
		indexes.push_back(3);

		Insert(L"FillRect2D",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

	//line rect mesh
	{
		constexpr UINT VERTEX_COUNT = 4;
		tVertex vertexArray[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2
		vertexArray[0].pos = Vector3(-0.5f, 0.5f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		vertexArray[1].pos = Vector3(0.5f, 0.5f, 0.0f);
		vertexArray[1].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[1].uv = Vector2(1.0f, 0.0f);

		vertexArray[2].pos = Vector3(+0.5f, -0.5f, 0.0f);
		vertexArray[2].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[2].uv = Vector2(1.0f, 1.0f);

		vertexArray[3].pos = Vector3(-0.5f, -0.5f, 0.0f);
		vertexArray[3].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[3].uv = Vector2(0.0f, 1.0f);

		std::vector<UINT> indexes;
		indexes.reserve(10);

		indexes.push_back(0);
		indexes.push_back(1);
		indexes.push_back(2);
		indexes.push_back(3);
		indexes.push_back(0);


		Insert(L"LineRect2D",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

	//fill circle mesh
	{
		constexpr UINT VERTEX_COUNT = 100;
		tVertex vertexArray[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2
		
		// pivot
		vertexArray[0].pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		const float anglePer = 360.f / (VERTEX_COUNT - 1);

		for (int i = 1; i < VERTEX_COUNT; ++i)
		{
			const float y = sin(Deg2Rad(anglePer * (i - 1))) * 0.5f;
			const float x = cos(Deg2Rad(anglePer * (i - 1))) * 0.5f;		
			
			const float uvx  =  x * 0.5f;
			const float uvy  = -y * 0.5f;


			//cos(Rad2DE)

			vertexArray[i].pos = Vector3(x, y, 0.0f);
			vertexArray[i].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
			vertexArray[i].uv = Vector2(uvx, uvy);
		}

		std::vector<UINT> indexes;
		indexes.reserve(VERTEX_COUNT);

		//pivot
		for (int i = 0; i < VERTEX_COUNT - 2; ++i)
		{
			indexes.push_back(0);
			indexes.push_back(1 + i);
			indexes.push_back(2 + i);
		}

		indexes.push_back(1);
		indexes.push_back(0);
		indexes.push_back(VERTEX_COUNT - 1);

		


		Insert(L"FillCircle2D",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

	//line circle mesh
	{
		constexpr UINT VERTEX_COUNT = 100;
		tVertex vertexArray[VERTEX_COUNT] = {};
		//0---1
		//|   |
		//3---2

		// pivot
		vertexArray[0].pos = Vector3(0.0f, 0.0f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		const float anglePer = 360.f / (VERTEX_COUNT);

		for (int i = 0; i < VERTEX_COUNT; ++i)
		{
			const float x = cos(Deg2Rad(anglePer * (i - 1))) * 0.5f;
			const float y = sin(Deg2Rad(anglePer * (i - 1))) * 0.5f;

			const float uvx =  x + 0.5f;
			const float uvy = -y + 0.5f;

			vertexArray[i].pos = Vector3(x, y, 0.0f);
			vertexArray[i].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
			vertexArray[i].uv = Vector2(uvx, uvy);
		}

		std::vector<UINT> indexes;
		indexes.reserve(VERTEX_COUNT);

		//pivot
		for (int i = 0; i < VERTEX_COUNT; ++i)
		{
			indexes.push_back(i);
		}
		indexes.push_back(0);

		Insert(L"LineCircle2D",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

	//line mesh
	{
		constexpr UINT VERTEX_COUNT = 2;
		tVertex vertexArray[VERTEX_COUNT] = {};

		vertexArray[0].pos = Vector3(-0.5f, 0.0f, 0.0f);
		vertexArray[0].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[0].uv = Vector2(0.0f, 0.0f);

		vertexArray[1].pos = Vector3(0.5f, 0.0f, 0.0f);
		vertexArray[1].color = Vector4(1.0f, 0.0f, 1.0f, 1.0f);
		vertexArray[1].uv = Vector2(1.0f, 1.0f);		

		std::vector<UINT> indexes;
		indexes.reserve(10);

		indexes.push_back(0);
		indexes.push_back(1);

		Insert(L"Line",
			new Mesh(vertexArray, VERTEX_COUNT, sizeof(tVertex),
				indexes.data(), indexes.size(), sizeof(UINT)));
	}

#pragma endregion

#pragma region Shader
	//Fill2D Debug
	{
		Shader* const debugShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSFillDebug2D.hlsl", L"main",
				L"\\Shader\\PSFillDebug2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::None,
				eBSType::AlphaBlend);
		Insert(L"FillDebug2D", debugShader);
	}

	//Line2D Debug
	{
		Shader* const debugShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_LINESTRIP,
				L"\\Shader\\VSLineDebug2D.hlsl", L"main",
				L"\\Shader\\PSLineDebug2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::None,
				eBSType::AlphaBlend);
		Insert(L"LineDebug2D", debugShader);
	}

	//Grid2D Debug
	{
		Shader* const debugShader =
			new Shader(D3D11_PRIMITIVE_TOPOLOGY::D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST,
				L"\\Shader\\VSGrid2D.hlsl", L"main",
				L"\\Shader\\PSGrid2D.hlsl", L"main",
				eSMType::Default,
				eRSType::CullNone,
				eDSType::None,
				eBSType::AlphaBlend);
		Insert(L"DebugGrid2D", debugShader);
	}


#pragma endregion

}

ResourceManager::~ResourceManager()
{
	for (Dictionary& item : mResources)
	{
		memory::safe::DeleteUnorderedMap(item);
	}
}
