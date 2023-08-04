#include "pch.h"
#include "SimpleEditorCollider2D.h"
#include "Components.h"

#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
#include <Engine/Color.h>
#include <Engine/EngineMath.h>
#include <Engine/EngineFile.h>
#include <Engine/String.h>
SimpleEditorCollider2D::SimpleEditorCollider2D()
	: ScriptComponent(eScriptComponentType::SimpleEditorCollider2D)
{
}

SimpleEditorCollider2D::~SimpleEditorCollider2D()
{
}

void SimpleEditorCollider2D::initialize()
{
}

void SimpleEditorCollider2D::update()
{
	const RenderTargetRenderer* const renderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
	DebugRenderer2D* const debugRender = renderer->GetDebugRenderer2D();
	Camera* const camera = renderer->GetRegisteredRenderCamera(eCameraPriorityType::Main);

	static bool isDraw = true;

	static Vector3 startPos = Vector3(0.f, 0.f, 0.f);
	static Vector3 endPos = Vector3(0.f, 0.f, 0.f);
	static eCollider2DType type = eCollider2DType::Box;


	if (isDraw)
	{
		debugRender->DrawGrid2D(Vector3(0.f, 0.f, 0.f), Vector2(32.f, 32.f), XMUINT2(20000, 20000), 0.f,
			helper::Color::YELLOW);
	}

	if (gInput->GetKeyDown(eKeyCode::P))
	{
		isDraw = !isDraw;
	}

	if (gInput->GetKeyDown(eKeyCode::O))
	{
		type = type == eCollider2DType::Box ? eCollider2DType::Line : eCollider2DType::Box;
	}

	if (gInput->GetKey(eKeyCode::LCONTROL) &&
		gInput->GetKey(eKeyCode::LSHIFT) &&
		gInput->GetKey(eKeyCode::S))
	{
		helper::DialogPath path = helper::SaveDialog();
		helper::FileWriter writer(path);

		for (tEditCollider& editCollider : mEditColliders)
		{
			constexpr UINT BUFFER_LEN = 256;
			wchar_t buffer[BUFFER_LEN] = { 0, };

			writer.WriteLine(L"{");

			writer.WriteLine(L"GameObject* const wall = new GameObject();");

			if (editCollider.type == eCollider2DType::Box)
			{
				writer.WriteLine(L"//[RectCollider]");
				


				Vector3 centerPos = (editCollider.startPos + editCollider.endPos) * 0.5f;
				Vector3 scale = editCollider.endPos - editCollider.startPos;

				scale.x = fabsf(scale.x);
				scale.y = fabsf(scale.y);

				writer.WriteLine(L"wall->AddComponent<RectCollider2D>();");

				swprintf_s(buffer, BUFFER_LEN,
					L"wall->GetComponent<Transform>()->SetPosition(%.f, %.f, %.f);", centerPos.x, centerPos.y, centerPos.z);
				writer.WriteLine(buffer);

				ZeroMemory(buffer, BUFFER_LEN);	

				swprintf_s(buffer, BUFFER_LEN,
					L"wall->GetComponent<RectCollider2D>()->SetSize(Vector2(%.f, %.f));", scale.x, scale.y);

				writer.WriteLine(buffer);

				writer.WriteLine(L"AddGameObject(wall, eLayerType::Wall);");
			}
			else if (editCollider.type == eCollider2DType::Line)
			{
				writer.WriteLine(L"//[LineCollider]");

				//platform->AddComponent<LineCollider2D>();
				writer.WriteLine(L"wall->AddComponent<LineCollider2D>();");

				Vector3 sp = editCollider.startPos;
				Vector3 ep = editCollider.endPos;

				//write startpos using swprintf_s 
				writer.WriteLine(L"wall->GetComponent<Transform>()->SetPosition(0.f, 0.f, 0.f);");

				ZeroMemory(buffer, BUFFER_LEN);

				swprintf_s(buffer, BUFFER_LEN,
					L"wall->GetComponent<LineCollider2D>()->SetPoints(%.f, %.f, %.f, %.f);", 
					sp.x, sp.y, ep.x, ep.y);

				writer.WriteLine(buffer);

				writer.WriteLine(L"AddGameObject(wall, eLayerType::Slope);");
			}

			//
			//{
			//	GameObject* const wall = new GameObject();
			//	//[RectCollider]
			//	wall->AddComponent<LineCollider2D>();
			//	wall->GetComponent<Transform>()->SetPosition(0, 0, 0);
			//	wall->GetComponent<LineCollider2D>()->SetPoints(1.f, 1.f, 1.f, 1.f);
			//	AddGameObject(wall, eLayerType::Slope);
			//}
			//AddGameObject(wall, eLayerType::Default);

			writer.WriteLine(L"}");

			writer.WriteLine(L"");
		}
	}


	if (gInput->GetKeyDown(eKeyCode::N))
	{
		if (!mEditColliders.empty())
		{
			mEditColliders.pop_back();
		}
	}

	Vector3 mousePos = helper::WindowScreenMouseToWorld3D(camera);
	XMINT2 index = helper::GridIndex(mousePos, Vector2(32.f, 32.f), XMUINT2(20000, 20000));
	const Vector3 gridPos =
		helper::GridIndexToWorldPosition(index, Vector2(32.f, 32.f), XMUINT2(20000, 20000));



	if (type == eCollider2DType::Box)
	{
		debugRender->DrawFillRect2D(gridPos, Vector2(32.f, 32.f), 0.f, Vector4(1.f, 0.f, 0.f, 0.5f));
	}
	else if (type == eCollider2DType::Line)
	{
		debugRender->DrawLine2D(gridPos, gridPos + Vector3(32.f, 32.f, 0.f), 0.f, Vector4(1.f, 0.f, 0.f, 0.5f));
	}


	if (gInput->GetKeyDown(eKeyCode::LBTN))
	{
		startPos.x = gridPos.x - 16.f;
		startPos.y = gridPos.y + 16.f;
	}
	else if (gInput->GetKey(eKeyCode::LBTN))
	{
		endPos.x = gridPos.x + 16.f;
		endPos.y = gridPos.y - 16.f;

		debugRender->DrawFillRect2D2(startPos, endPos, 0.f, Vector4(0.f, 1.f, 0.f, 0.5f));
	}
	else if (gInput->GetKeyUp(eKeyCode::LBTN))
	{
		tEditCollider editInfo;

		editInfo.startPos = startPos;
		editInfo.endPos = endPos;
		editInfo.type = type;

		mEditColliders.push_back(editInfo);
		//debugRender->DrawFillRect2D2(startPos, endPos, 500.f, Vector4(1.f, 1.f, 0.f, 0.5f));       
	}


	for (tEditCollider& editCollider : mEditColliders)
	{
		if (editCollider.type == eCollider2DType::Box)
		{
			debugRender->DrawFillRect2D2(editCollider.startPos, editCollider.endPos,
				0.f, Vector4(1.f, 1.f, 0.f, 0.5f));
		}
		else if (editCollider.type == eCollider2DType::Line)
		{
			debugRender->DrawLine2D(editCollider.startPos, editCollider.endPos,
				0.f, Vector4(0.f, 1.f, 0.f, 1.0f));
		}
	}





}

void SimpleEditorCollider2D::lateUpdate()
{
}
