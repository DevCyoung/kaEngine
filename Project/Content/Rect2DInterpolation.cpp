#include "pch.h"
#include "Rect2DInterpolation.h"
#include "Components.h"
#include <Engine/EngineMath.h>
#include <Engine/GameSystem.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
#include <Engine/Physics2D.h>
#include <Engine/Color.h>
#include "GameManager.h"

Rect2DInterpolation::Rect2DInterpolation()
	: ScriptComponent(eScriptComponentType::Rect2DInterpolation)
	, mbPlatform(true)
	, mbCollisionDir{}
	, mInterpolationPos{}
{
}

Rect2DInterpolation::~Rect2DInterpolation()
{
}


void Rect2DInterpolation::initialize()
{
}

void Rect2DInterpolation::update()
{
	Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

	if (mbCollisionDir[static_cast<UINT>(eWallType::Floor)] ||
		mbCollisionDir[static_cast<UINT>(eWallType::Slope)])
	{
		rigidbody->TurnOnGround();
	}
	else
	{
		rigidbody->TurnOffGround();
	}
}

void Rect2DInterpolation::lateUpdate()
{
	ZeroMemory(mbCollisionDir, sizeof(bool) * static_cast<UINT>(eWallType::End));
	ZeroMemory(mInterpolationPos, sizeof(Vector2) * static_cast<UINT>(eWallType::End));
}

void Rect2DInterpolation::lastUpdate()
{
	if (GameManager::GetInstance()->GetRewindManager()->GetRewindState() == eRewindState::Rewind)
	{
		return;
	}

	//RenderTargetRenderer* const renderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
	//DebugRenderer2D* const debugRenderer = renderer->GetDebugRenderer2D();

	Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();
	Transform* const transform = GetOwner()->GetComponent<Transform>();
	Matrix transMat = transform->GetWorldMatrix();

	Vector2 velocity = rigidbody->GetVelocity();
	Vector3 position = transform->GetPosition();

	const Vector3& WORLD_POS = transMat.Translation();

	////check Slope	
	Physics2D* const physics = GetOwner()->GetGameSystem()->GetPhysics2D();

	const Matrix& COL_MAT = GetOwner()->GetComponent<RectCollider2D>()->GetColliderWorldMatrix();
	
	Vector3 colHalfSize = XMVector3TransformNormal(Vector3(0.5f, 0.0f, 0.0f), COL_MAT);
	Vector3 COL_POS = COL_MAT.Translation();

	Vector2 LRP  = Vector2(COL_POS.x - abs(colHalfSize.x) + 1.f, WORLD_POS.y);
	Vector2 RRP  = Vector2(COL_POS.x + abs(colHalfSize.x) - 1.f, WORLD_POS.y);

	Vector4 LEFT_RAY_COLOR = helper::Color::WHITE;
	Vector4 RIGHT_RAY_COLOR = helper::Color::WHITE;

	const float RAY_DIST = 37.f;

	RayCast2DHitInfo info = {};

	float platFormInterSizeY = 0.f;

	if (IsCollisionWalPlatform())
	{		
		Vector3 down = XMVector3TransformCoord(Vector3(0.0f, -0.5f, 0.0f), COL_MAT);
		const Vector2 startPos = mInterpolationPos[static_cast<UINT>(eWallType::Platform)];
		platFormInterSizeY = abs(abs(startPos.y) - abs(down.y));
	}

	if (IsCollisionWalPlatform() && mbPlatform && velocity.y <= 0.f && platFormInterSizeY <= 1.f)
	{		
		mbCollisionDir[static_cast<UINT>(eWallType::Floor)] = true;

		velocity.y = 0.f;

		position.y += platFormInterSizeY;
		transMat._42 += platFormInterSizeY;
	}
	else if (physics->RayCastHit2D(LRP, Vector2::Down, RAY_DIST, eLayerType::LeftSlope, &info))
	{
		mbCollisionDir[static_cast<UINT>(eWallType::Slope)] = true;

		float interSizeY = abs(info.hitPos.y - (LRP.y - RAY_DIST));
		position.y   += interSizeY - 1.0f;
		transMat._42 += interSizeY - 1.0f;
		LEFT_RAY_COLOR = Vector4(1.f, 0.f, 1.f, 1.f);
	}
	else if (physics->RayCastHit2D(RRP, Vector2::Down, RAY_DIST, eLayerType::RightSlope, &info))
	{	
		mbCollisionDir[static_cast<UINT>(eWallType::Slope)] = true;

		float interSizeY = abs(info.hitPos.y - (RRP.y - RAY_DIST));
		position.y += interSizeY - 1.0f;
		transMat._42 += interSizeY - 1.0f;
		RIGHT_RAY_COLOR = Vector4(1.f, 0.f, 1.f, 1.f);
	}
	else
	{
		if (IsCollisionWallFloor())
		{
			const Vector2 interSize = mInterpolationPos[static_cast<UINT>(eWallType::Floor)];

			velocity.y = 0.f;
			position.y += interSize.y;
			transMat._42 += interSize.y;
		}		


		if (IsCollisionWallLeft())
		{
			const Vector2 interSize = mInterpolationPos[static_cast<UINT>(eWallType::Left)];

			velocity.x = 0.f;
			position.x += interSize.x;
			transMat._41 += interSize.x;
		}
		if (IsCollisionWallRight())
		{
			const Vector2 interSize = mInterpolationPos[static_cast<UINT>(eWallType::Right)];

			velocity.x = 0.f;
			position.x -= interSize.x;
			transMat._41 -= interSize.x;
		}

		if (IsCollisionWallCeiling())
		{
			const Vector2 interSize = mInterpolationPos[static_cast<UINT>(eWallType::Ceiling)];

			velocity.y = 0.f;
			position.y -= interSize.y + 1.f;
			transMat._42 -= interSize.y + 1.f;
		}
	}


	/*debugRenderer->DrawLine2D2(Vector3(LRP.x, LRP.y, 0.f), Vector2::Down, RAY_DIST, 0.f, LEFT_RAY_COLOR);
	debugRenderer->DrawLine2D2(Vector3(RRP.x, RRP.y, 0.f), Vector2::Down, RAY_DIST, 0.f, RIGHT_RAY_COLOR);*/

	rigidbody->SetVelocity(velocity);
	transform->SetPosition(position);
	transform->SetWorldMatrix(transMat);
}

void Rect2DInterpolation::onCollisionEnter(Collider2D* other)
{
	onCollisionInterpolation(other);
}

void Rect2DInterpolation::onCollisionStay(Collider2D* other)
{
	onCollisionInterpolation(other);
}

void Rect2DInterpolation::onCollisionExit(Collider2D* other)
{
	(void)other;
}

void Rect2DInterpolation::onCollisionLeftWall(Collider2D* other, Vector2 width)
{
	if (mbCollisionDir[static_cast<UINT>(eWallType::Left)])
	{
		return;
	}

	mbCollisionDir[static_cast<UINT>(eWallType::Left)] = true;
	mInterpolationPos[static_cast<UINT>(eWallType::Left)] = width;
	(void)other;
}

void Rect2DInterpolation::onCollisionRightWall(Collider2D* other, Vector2 width)
{
	if (mbCollisionDir[static_cast<UINT>(eWallType::Right)])
	{
		return;
	}

	mbCollisionDir[static_cast<UINT>(eWallType::Right)] = true;
	mInterpolationPos[static_cast<UINT>(eWallType::Right)] = width;
	(void)other;
}

void Rect2DInterpolation::onCollisionDownWall(Collider2D* other, Vector2 width)
{
	if (mbCollisionDir[static_cast<UINT>(eWallType::Floor)])
	{
		return;
	}

	mbCollisionDir[static_cast<UINT>(eWallType::Floor)] = true;
	mInterpolationPos[static_cast<UINT>(eWallType::Floor)] = width;
	(void)other;
}

void Rect2DInterpolation::onCollisionUpWall(Collider2D* other, Vector2 width)
{
	if (mbCollisionDir[static_cast<UINT>(eWallType::Ceiling)])
	{
		return;
	}

	mbCollisionDir[static_cast<UINT>(eWallType::Ceiling)] = true;
	mInterpolationPos[static_cast<UINT>(eWallType::Ceiling)] = width;

	(void)other;
}

void Rect2DInterpolation::onCollisionInterpolation(Collider2D* const other)
{
	const Matrix& MAT = GetOwner()->GetComponent<RectCollider2D>()->GetColliderWorldMatrix();
	const Matrix& WALL_MAT = other->GetColliderWorldMatrix();

	const Vector2& INTER_SIZE = helper::math::GetBoxAndBoxInterBoxSize(MAT, WALL_MAT);

	const Vector3& POS = MAT.Translation();
	const Vector3& WALL_POS = WALL_MAT.Translation();

	const eLayerType OTHER_LAYER_TYPE = other->GetOwner()->GetLayer();

	if (OTHER_LAYER_TYPE == eLayerType::Wall)
	{
		if (INTER_SIZE.x >= INTER_SIZE.y)
		{
			if (POS.y >= WALL_POS.y)
			{
				onCollisionDownWall(other, INTER_SIZE);
			}
			else
			{
				onCollisionUpWall(other, INTER_SIZE);
			}

		}
		else
		{
			if (POS.x <= WALL_POS.x)
			{
				onCollisionRightWall(other, INTER_SIZE);
			}
			else
			{
				onCollisionLeftWall(other, INTER_SIZE);
			}
		}
	}
	else if (OTHER_LAYER_TYPE == eLayerType::Platform)
	{
		if (mbCollisionDir[static_cast<UINT>(eWallType::Platform)])
		{
			return;
		}

		const Vector3 startPos = other->GetStartPos();
		mbCollisionDir[static_cast<UINT>(eWallType::Platform)] = true;
		mInterpolationPos[static_cast<UINT>(eWallType::Platform)] = Vector2(startPos.x, startPos.y);
	}

}
