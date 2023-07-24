#include "pch.h"
#include "Engine.h"
#include "EngineMath.h"
#include "Camera.h"
#include "Transform.h"
#include "InputManager.h"

/*
* 게임 에서 사용하는 UI 좌표계는 윈도우 좌표계와 동일하게 사용합니다.
* 윈도우 좌표계는 왼쪽 상단이 (0, 0)이고 오른쪽 하단이 (width, height)입니다.
*/

namespace helper
{
	Vector2 RenderTargetToWorldUI(const Vector2& renderTargetMousePos, const Vector2& renderTargetSize)
	{
		return Vector2(renderTargetMousePos.x - renderTargetSize.x / 2, -renderTargetMousePos.y + renderTargetSize.y / 2);
	}

	Vector3 ScreenMouseToWorld3D(const Vector3& screenMousePos, 
		const Vector2& screenSize, const Camera* const camera)
	{
		Viewport viewport = {};
		viewport.width = screenSize.x;
		viewport.height = screenSize.y;
		viewport.x = 0;
		viewport.y = 0;
		viewport.minDepth = 0.0f;
		viewport.maxDepth = 1.0f;

		const Vector3& mouseWorldPos3D =
			viewport.Unproject(screenMousePos, camera->GetProjection(), camera->GetView(), Matrix::Identity);

		return mouseWorldPos3D;
	}

	Vector3 WindowScreenMouseToWorld3D(const Camera* const camera)
	{
		const Vector2& WINDOW_MOUSE_2D_POS = gInput->GetWindowMousePos();
		const Vector3& WINDOW_MOUSE_3D_POS = Vector3(WINDOW_MOUSE_2D_POS.x, WINDOW_MOUSE_2D_POS.y, 0.0f);
		const Vector2& WINDOW_SCREEN_SIZE = gEngine->GetWindowScreenSize();

		return ScreenMouseToWorld3D(WINDOW_MOUSE_3D_POS, WINDOW_SCREEN_SIZE, camera);
	}

	XMINT2 GridIndex(const Vector3& selectWorldPos,
		const Vector2& cellSize, const XMUINT2& tileCount)
	{
		Vector2 selectPointToCenterPos = Vector2(selectWorldPos.x, -selectWorldPos.y);

		selectPointToCenterPos.x += (cellSize.x * tileCount.x) / 2.f;
		selectPointToCenterPos.y += (cellSize.y * tileCount.y) / 2.f;

		int x = static_cast<int>(selectPointToCenterPos.x / cellSize.x);
		int y = static_cast<int>(selectPointToCenterPos.y / cellSize.y);

		if (selectPointToCenterPos.x < 0.f)
		{
			x = -1;
		}
		if (selectPointToCenterPos.y < 0.f)
		{
			y = -1;
		}

		return XMINT2(x, y);
	}

	Vector3 GridIndexToWorldPosition(const XMINT2& gridIndex,
		const Vector2& cellSize, const XMUINT2& tileCount)
	{
		Vector3 rectPos = Vector3::Zero;

		rectPos.x -= (cellSize.x * tileCount.x) / 2;
		rectPos.y += (cellSize.y * tileCount.y) / 2;

		rectPos.x += (gridIndex.x * cellSize.x) + (cellSize.x / 2);
		rectPos.y -= (gridIndex.y * cellSize.y) + (cellSize.y / 2);

		return rectPos;
	}

	bool IsInGrid(const XMINT2& gridIndex, const XMUINT2& tileCount)
	{
		XMINT2 countXY = {};

		countXY.x = static_cast<int>(tileCount.x);
		countXY.y = static_cast<int>(tileCount.y);

		return 0 <= gridIndex.x && gridIndex.x < countXY.x &&
			0 <= gridIndex.y && gridIndex.y < countXY.y;
	}
}

namespace helper::math
{
	void INT2MinAndMax(const XMINT2& a, const XMINT2& b, XMINT2* const outMin, XMINT2* const outMax)
	{
		Assert(outMin, WCHAR_IS_NULLPTR);
		Assert(outMax, WCHAR_IS_NULLPTR);

		outMin->x = min(a.x, b.x);
		outMin->y = min(a.y, b.y);

		outMax->x = max(a.x, b.x);
		outMax->y = max(a.y, b.y);
	}

	float LerpCosBtwZeroAndOne(const float x)
	{
		return (cos(x) + 1.f) / 2.f;
	}

	float LerpSinBtwZeroAndOne(const float x)
	{
		return (sin(x) + 1.f) / 2.f;
	}
}





namespace helper::rand
{
	static std::random_device rd;
	static std::mt19937 gen(rd());
	int RandInt(const int a, const int b)
	{
		std::uniform_int_distribution<int> dis(a, b);
	
		return dis(gen);
	}
}