#include "pch.h"
#include "Rect2DInterpolation.h"
#include "Components.h"
#include <Engine/EngineMath.h>
#include <Engine/GameSystem.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>


Rect2DInterpolation::Rect2DInterpolation()
	: ScriptComponent(eScriptComponentType::Rect2DInterpolation)
	, mbCollisionDir{}
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

	if (mbCollisionDir[static_cast<UINT>(Dir::Down)])
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
	memset(mbCollisionDir, false, 5);
}

void Rect2DInterpolation::onCollisionEnter(Collider2D* other)
{
	if (other->GetOwner()->GetLayer() != eLayerType::Wall)
	{
		return;
	}

	RectCollider2D* const collider = GetOwner()->GetComponent<RectCollider2D>();

	const Matrix& mat = collider->GetColliderWorldMatrix();
	const Matrix& WallMat = other->GetColliderWorldMatrix();

	const Vector3& POS = mat.Translation();
	const Vector3& WALL_POS = WallMat.Translation();

	Vector3 SCALE = XMVector3TransformNormal(Vector3::One, mat);
	SCALE.x = abs(SCALE.x);
	SCALE.y = abs(SCALE.y);

	const Vector3& WALL_SCALE = XMVector3TransformNormal(Vector3::One, WallMat);

	const Vector3& LT1 = POS - SCALE / 2;
	const Vector3& LT2 = WALL_POS - WALL_SCALE / 2;

	const Vector3& RB1 = POS + SCALE / 2;
	const Vector3& RB2 = WALL_POS + WALL_SCALE / 2;

	const float MAX_LEFT_UP_X = max(LT1.x, LT2.x);
	const float MAX_LEFT_UP_Y = max(LT1.y, LT2.y);

	const float MAX_RIGHT_DOWN_X = min(RB1.x, RB2.x);
	const float MAX_RIGHT_DOWN_Y = min(RB1.y, RB2.y);



	const float WIDTH = abs(MAX_RIGHT_DOWN_X - MAX_LEFT_UP_X);
	const float HEIGHT = abs(MAX_RIGHT_DOWN_Y - MAX_LEFT_UP_Y);


	const Vector2 width = Vector2(WIDTH, HEIGHT);

	RenderTargetRenderer* renderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
	DebugRenderer2D* debugRenderer = renderer->GetDebugRenderer();

	debugRenderer->DrawFillRect2D2(Vector3(MAX_LEFT_UP_X, MAX_LEFT_UP_Y, 1.f),
		Vector3(MAX_RIGHT_DOWN_X, MAX_RIGHT_DOWN_Y, 1.f),
		0.f,
		Vector4(1.f, 1.f, 1.f, 1.f));

	(void)WIDTH;
	(void)HEIGHT;


	//천장이거나 바닥
	if (WIDTH >= HEIGHT)
	{
		//내가더위에있다면 (y가더큼)
		if (POS.y >= WALL_POS.y)
		{
			//이전 프레임 충돌 확인
			/*iter->second = COLLIDE_DIR::DOWN;
			++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
			this->GetOwner()->OnTriggerEnterDown(_pOther);*/
			mbCollisionDir[static_cast<UINT>(Dir::Down)] = true;
			onCollisionDownWall(collider, width);

		}
		//천장
		else
		{
			/*iter->second = COLLIDE_DIR::UP;
			++m_curWallDir[(UINT)COLLIDE_DIR::UP];
			this->GetOwner()->OnTriggerEnterUp(_pOther);*/
			mbCollisionDir[static_cast<UINT>(Dir::Up)] = true;
			onCollisionUpWall(collider, width);
		}

	}
	//왼쪽 혹은 오른쪽
	else
	{
		//오른쪽벽
		if (POS.x <= WALL_POS.x)
		{
			//if (lineCol != nullptr)
			//{
			//	iter->second = COLLIDE_DIR::DOWN;
			//	++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
			//	this->GetOwner()->OnTriggerEnterDown(_pOther);
			//}
			//else
			//{
			//	iter->second = COLLIDE_DIR::RIGHT;
			//	++m_curWallDir[(UINT)COLLIDE_DIR::RIGHT];
			//	this->GetOwner()->OnTriggerEnterRight(_pOther);
			//}
			mbCollisionDir[static_cast<UINT>(Dir::Right)] = true;
			onCollisionRightWall(collider, width);

		}
		//왼쪽벽
		else
		{
			/*if (lineCol != nullptr)
			{
				iter->second = COLLIDE_DIR::DOWN;
				++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
				this->GetOwner()->OnTriggerEnterDown(_pOther);
			}
			else
			{
				iter->second = COLLIDE_DIR::LEFT;
				++m_curWallDir[(UINT)COLLIDE_DIR::LEFT];
				this->GetOwner()->OnTriggerEnterLeft(_pOther);
			}*/
			mbCollisionDir[static_cast<UINT>(Dir::Left)] = true;
			onCollisionLeftWall(collider, width);
		}
	}



	//Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();
	//
	//rigidbody->TurnOnGround();
	//rigidbody->TurnOffGravity();
	//rigidbody->SetVelocity(Vector2::Zero);


	(void)other;
}

#include <Engine/EngineMath.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
#include <Engine/GameSystem.h>
void Rect2DInterpolation::onCollisionStay(Collider2D* other)
{
	

	RectCollider2D* const collider = GetOwner()->GetComponent<RectCollider2D>();

	const Matrix& mat = collider->GetColliderWorldMatrix();
	const Matrix& WallMat = other->GetColliderWorldMatrix();

	const Vector3& POS = mat.Translation();
	const Vector3& WALL_POS = WallMat.Translation();

	const Vector3& WALL_SCALE = XMVector3TransformNormal(Vector3::One, WallMat);

	Vector3 SCALE = XMVector3TransformNormal(Vector3::One, mat);
	SCALE.x = abs(SCALE.x);
	SCALE.y = abs(SCALE.y);

	const Vector3& LT1 = POS - SCALE / 2;
	const Vector3& LT2 = WALL_POS - WALL_SCALE / 2;

	const Vector3& RB1 = POS + SCALE / 2;
	const Vector3& RB2 = WALL_POS + WALL_SCALE / 2;

	Vector3 vertexPosArray[2] =
	{
		Vector3(-0.5f, 0.5f, 0.f), Vector3(0.5f, 0.5f, 0.f),
	};

	Vector3 l = XMVector3TransformCoord(vertexPosArray[0], WallMat);
	Vector3 r = XMVector3TransformCoord(vertexPosArray[1], WallMat);


	// lr s
	float x1 = LT1.x;
	float y1 = LT1.y;
	float x2 = LT1.x;
	float y2 = RB1.y;

	

	float x3 = l.x;
	float y3 = l.y;
	float x4 = r.x;
	float y4 = r.y;


	if (y3 < y4)
	{
		x1 = RB1.x;
		y1 = LT1.y;
		x2 = RB1.x;
		y2 = RB1.y;
	}

	float inX = 0.f;
	float inY = 0.f;

	GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetDebugRenderer()->DrawLine2D(
		Vector3(x3, y3, 1.f), Vector3(x4, y4, 1.f), 0.f, Vector4(1.f, 1.f, 1.f, 1.f));

	if (other->GetOwner()->GetLayer() == eLayerType::Slope)
	{
		Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

		mbCollisionDir[static_cast<UINT>(Dir::Down)] = true;
		mbCollisionDir[static_cast<UINT>(Dir::Slop)] = true;

		Vector2 velocity = rigidbody->GetVelocity();
		velocity.y = 0.f;
		rigidbody->SetVelocity(velocity);

		helper::math::LineAndLineCollision(x1, y1, x2, y2, x3, y3, x4, y4, &inX, &inY);

		GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetDebugRenderer()->DrawFillCircle2D(
			Vector3(inX, inY, 0.f), 4.f, 0.f, Vector4(1.f, 0.f, 1.f, 1.f));

		GetOwner()->GetGameSystem()->GetRenderTargetRenderer()->GetDebugRenderer()->DrawFillCircle2D(
			Vector3(x1, y1, 0.f), 4.f, 0.f, Vector4(0.f, 0.f, 1.f, 1.f));

		if (inY >= y1)
		{
			Matrix mat2 = GetOwner()->GetComponent<Transform>()->GetWorldMatrix();
			mat2._42 += inY - y1 - 2;
			GetOwner()->GetComponent<Transform>()->SetWorldMatrix(mat2);


			Vector3 Pos = GetOwner()->GetComponent<Transform>()->GetPosition();
			Pos.y += inY - y1 - 2;
			GetOwner()->GetComponent<Transform>()->SetPosition(Pos);			
		}

		Vector2 velocity2 = rigidbody->GetVelocity();
		velocity2.y = 0.f;
		rigidbody->SetVelocity(velocity2);
	}

	if (other->GetOwner()->GetLayer() == eLayerType::Wall)
	{
		const float MAX_LEFT_UP_X = max(LT1.x, LT2.x);
		const float MAX_LEFT_UP_Y = max(LT1.y, LT2.y);

		const float MAX_RIGHT_DOWN_X = min(RB1.x, RB2.x);
		const float MAX_RIGHT_DOWN_Y = min(RB1.y, RB2.y);



		const float WIDTH = abs(MAX_RIGHT_DOWN_X - MAX_LEFT_UP_X);
		const float HEIGHT = abs(MAX_RIGHT_DOWN_Y - MAX_LEFT_UP_Y);


		const Vector2 width = Vector2(WIDTH, HEIGHT);

		RenderTargetRenderer* renderer = GetOwner()->GetGameSystem()->GetRenderTargetRenderer();
		DebugRenderer2D* debugRenderer = renderer->GetDebugRenderer();

		debugRenderer->DrawFillRect2D2(Vector3(MAX_LEFT_UP_X, MAX_LEFT_UP_Y, 1.f),
			Vector3(MAX_RIGHT_DOWN_X, MAX_RIGHT_DOWN_Y, 1.f),
			0.f,
			Vector4(1.f, 1.f, 1.f, 1.f));

		(void)WIDTH;
		(void)HEIGHT;


		//천장이거나 바닥
		if (WIDTH >= HEIGHT)
		{
			//내가더위에있다면 (y가더큼)
			if (POS.y >= WALL_POS.y)
			{
				//이전 프레임 충돌 확인
				/*iter->second = COLLIDE_DIR::DOWN;
				++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
				this->GetOwner()->OnTriggerEnterDown(_pOther);*/
				mbCollisionDir[static_cast<UINT>(Dir::Down)] = true;
				onCollisionDownWall(collider, width);

			}
			//천장
			else
			{
				/*iter->second = COLLIDE_DIR::UP;
				++m_curWallDir[(UINT)COLLIDE_DIR::UP];
				this->GetOwner()->OnTriggerEnterUp(_pOther);*/
				mbCollisionDir[static_cast<UINT>(Dir::Up)] = true;
				onCollisionUpWall(collider, width);
			}

		}
		//왼쪽 혹은 오른쪽
		else
		{
			//오른쪽벽
			if (POS.x <= WALL_POS.x)
			{
				//if (lineCol != nullptr)
				//{
				//	iter->second = COLLIDE_DIR::DOWN;
				//	++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
				//	this->GetOwner()->OnTriggerEnterDown(_pOther);
				//}
				//else
				//{
				//	iter->second = COLLIDE_DIR::RIGHT;
				//	++m_curWallDir[(UINT)COLLIDE_DIR::RIGHT];
				//	this->GetOwner()->OnTriggerEnterRight(_pOther);
				//}
				mbCollisionDir[static_cast<UINT>(Dir::Right)] = true;
				onCollisionRightWall(collider, width);
		

			}
			//왼쪽벽
			else
			{
				/*if (lineCol != nullptr)
				{
					iter->second = COLLIDE_DIR::DOWN;
					++m_curWallDir[(UINT)COLLIDE_DIR::DOWN];
					this->GetOwner()->OnTriggerEnterDown(_pOther);
				}
				else
				{
					iter->second = COLLIDE_DIR::LEFT;
					++m_curWallDir[(UINT)COLLIDE_DIR::LEFT];
					this->GetOwner()->OnTriggerEnterLeft(_pOther);
				}*/
				mbCollisionDir[static_cast<UINT>(Dir::Left)] = true;
				onCollisionLeftWall(collider, width);
			}
		}



		//Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();
		//
		//rigidbody->TurnOnGround();
		//rigidbody->TurnOffGravity();
		//rigidbody->SetVelocity(Vector2::Zero);


		(void)other;
	}


}

void Rect2DInterpolation::onCollisionExit(Collider2D* other)
{
	//Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();
	//
	//
	//rigidbody->TurnOffGround();
	//rigidbody->TurnOnGravity();
	//


	(void)other;
}



void Rect2DInterpolation::onCollisionLeftWall(Collider2D* other, Vector2 width)
{
	Matrix mat = GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

	Vector3 Pos = GetOwner()->GetComponent<Transform>()->GetPosition();

	Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();	

	if (mbCollisionDir[static_cast<UINT>(Dir::Left)])
	{
		mat._41 += width.x;
		GetOwner()->GetComponent<Transform>()->SetWorldMatrix(mat);

		Pos.x += width.x;
		GetOwner()->GetComponent<Transform>()->SetPosition(Pos);

		Vector2 velocity = rigidbody->GetVelocity();
		velocity.x = 0.f;
		rigidbody->SetVelocity(velocity);
	}

	(void)other;
}

void Rect2DInterpolation::onCollisionRightWall(Collider2D* other, Vector2 width)
{
	Matrix mat = GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

	Vector3 Pos = GetOwner()->GetComponent<Transform>()->GetPosition();

	Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

	if (mbCollisionDir[static_cast<UINT>(Dir::Right)])
	{
		mat._41 -= width.x;
		GetOwner()->GetComponent<Transform>()->SetWorldMatrix(mat);

		Pos.x -= width.x;
		GetOwner()->GetComponent<Transform>()->SetPosition(Pos);

		Vector2 velocity = rigidbody->GetVelocity();
		velocity.x = 0.f;
		rigidbody->SetVelocity(velocity);
	}

	(void)other;
}

void Rect2DInterpolation::onCollisionDownWall(Collider2D* other, Vector2 width)
{
	Matrix mat = GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

	Vector3 Pos = GetOwner()->GetComponent<Transform>()->GetPosition();

	Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

	if (mbCollisionDir[static_cast<UINT>(Dir::Down)])
	{
		mat._42 += width.y;
		GetOwner()->GetComponent<Transform>()->SetWorldMatrix(mat);

		Pos.y += width.y;
		GetOwner()->GetComponent<Transform>()->SetPosition(Pos);

		Vector2 velocity = rigidbody->GetVelocity();
		velocity.y = 0.f;
		rigidbody->SetVelocity(velocity);
	}

	(void)other;
}

void Rect2DInterpolation::onCollisionUpWall(Collider2D* other, Vector2 width)
{
	Matrix mat = GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

	Vector3 Pos = GetOwner()->GetComponent<Transform>()->GetPosition();

	Rigidbody2D* const rigidbody = GetOwner()->GetComponent<Rigidbody2D>();

	if (mbCollisionDir[static_cast<UINT>(Dir::Up)])
	{
		mat._42 -= width.y + 1.f;
		GetOwner()->GetComponent<Transform>()->SetWorldMatrix(mat);

		Pos.y -= width.y + 1.f;
		GetOwner()->GetComponent<Transform>()->SetPosition(Pos);

		Vector2 velocity = rigidbody->GetVelocity();
		velocity.y = 0.f;
		rigidbody->SetVelocity(velocity);
	}

	(void)other;
}

