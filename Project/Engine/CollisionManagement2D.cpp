#include "pch.h"
#include "CollisionManagement2D.h"
#include "Scene.h"
#include "Layer.h"
#include "GameObject.h"
#include "RectCollider2D.h"
#include "EngineMath.h"
#include "Transform.h"


/*
* Circle and Box Test
* http://jeffreythompson.org/collision-detection/circle-rect.php
*/

CollisionManagement2D::CollisionManagement2D()
	: mCollisionMatrix{ 0, }
	, mCollisionCheckMap()
	, mRenderTargetRenderer(nullptr)
{
}

CollisionManagement2D::~CollisionManagement2D()
{
}

void CollisionManagement2D::TurnOnAllCollisionLayer()
{
	for (UINT& mat : mCollisionMatrix)
	{
		mat = 0XFFFFFFFF;
	}
}

void CollisionManagement2D::TurnOffAllCollisionLayer()
{
	for (UINT& mat : mCollisionMatrix)
	{
		mat = 0;
	}
}

void CollisionManagement2D::TurnOnCollisionLayer(const eLayerType left, const eLayerType right)
{
	// row <= colum
	UINT row = static_cast<UINT>(left);
	UINT col = static_cast<UINT>(right);

	if (row > col)
	{
		UINT iTemp = col;
		col = row;
		row = iTemp;
	}

	mCollisionMatrix[row] |= (1 << col);
}

void CollisionManagement2D::TurnOffCollisionLayer(const eLayerType left, const eLayerType right)
{
	// row <= colum
	UINT row = static_cast<UINT>(left);
	UINT col = static_cast<UINT>(right);

	if (row > col)
	{
		const UINT iTemp = col;
		col = row;
		row = iTemp;
	}

	mCollisionMatrix[row] &= ~(1 << col);
}

void CollisionManagement2D::phisicsUpdate(Scene* const scene)
{
	for (UINT row = 0; row < static_cast<UINT>(eLayerType::End); ++row)
	{
		for (UINT col = row; col < static_cast<UINT>(eLayerType::End); ++col)
		{
			if (!(mCollisionMatrix[row] & (1 << col)))
			{
				continue;
			}

			const Layer& left = scene->mLayers[row];
			const Layer& right = scene->mLayers[col];

			const std::vector<GameObject*>& leftGameObjects = left.GetGameObjects();
			const std::vector<GameObject*>& rightGameObjects = right.GetGameObjects();

			if (row == col)
			{
				for (UINT i = 0; i < leftGameObjects.size(); ++i)
				{
					for (UINT j = i + 1; j < rightGameObjects.size(); ++j)
					{
						collisionGameObject(leftGameObjects[i], rightGameObjects[j]);
					}
				}
			}
			else
			{
				for (UINT i = 0; i < leftGameObjects.size(); ++i)
				{
					for (UINT j = 0; j < rightGameObjects.size(); ++j)
					{
						collisionGameObject(leftGameObjects[i], rightGameObjects[j]);
					}
				}
			}
		}
	}
}

void CollisionManagement2D::collisionGameObject(const GameObject* const leftGameObejct,
	const GameObject* const rightGameObejct)
{
	Collider2D* const leftCollider = leftGameObejct->GetComponentOrNull<Collider2D>();
	Collider2D* const rightCollider = rightGameObejct->GetComponentOrNull<Collider2D>();

	if (leftCollider == nullptr || rightCollider == nullptr)
	{
		return;
	}

	CollisionID collisionID = {};

	collisionID.entityID.LeftID = leftCollider->GetEntityID();
	collisionID.entityID.RightID = rightCollider->GetEntityID();

	std::unordered_map<UINT_PTR, bool>::iterator iter
		= mCollisionCheckMap.find(collisionID.id);

	if (iter == mCollisionCheckMap.end())
	{
		mCollisionCheckMap.insert(std::make_pair(collisionID.id, false));
		iter = mCollisionCheckMap.find(collisionID.id);
	}

	bool bExit = false;

	if (leftGameObejct->GetState() == GameObject::eState::Destroy ||
		rightGameObejct->GetState() == GameObject::eState::Destroy)

	{
		bExit = true;
	}

	const eCollider2DType LEFT_COLLIDER_TYPE = leftCollider->GetCollideType();
	const eCollider2DType RIGHT_COLLIDER_TYPE = rightCollider->GetCollideType();

	bool bCollision = false;

	if (LEFT_COLLIDER_TYPE == RIGHT_COLLIDER_TYPE)
	{
		if (LEFT_COLLIDER_TYPE == eCollider2DType::Box)
		{
			bCollision = collisionBoxCollider2D(leftCollider, rightCollider);
		}
		else if (LEFT_COLLIDER_TYPE == eCollider2DType::Circle)
		{
			bCollision = collisionCircleCollider2D(leftCollider, rightCollider);
		}
		else
		{
			Assert(false, WCHAR_IS_INVALID_TYPE);
		}
	}
	else
	{
		if (eCollider2DType::Box == LEFT_COLLIDER_TYPE && eCollider2DType::Circle == RIGHT_COLLIDER_TYPE)
		{
			bCollision = collisionBoxAndCircleCollider2D(leftCollider, rightCollider);
		}
		else if (eCollider2DType::Box == RIGHT_COLLIDER_TYPE && LEFT_COLLIDER_TYPE == eCollider2DType::Circle)
		{
			bCollision = collisionBoxAndCircleCollider2D(rightCollider, leftCollider);
		}
		else
		{
			Assert(false, WCHAR_IS_INVALID_TYPE);
		}
	}

	if (bCollision)
	{
		if (bExit && iter->second)
		{
			leftCollider->OnCollisionExit(rightCollider);
			rightCollider->OnCollisionExit(leftCollider);
		}
		else if (iter->second)
		{			
			leftCollider->OnCollisionStay(rightCollider);
			rightCollider->OnCollisionStay(leftCollider);
		}
		else
		{			
			if (bExit == false)
			{
				leftCollider->OnCollisionEnter(rightCollider);
				rightCollider->OnCollisionEnter(leftCollider);
				iter->second = true;
			}
		}
	}
	else
	{		
		if (iter->second)
		{
			leftCollider->OnCollisionExit(rightCollider);
			rightCollider->OnCollisionExit(leftCollider);
			iter->second = false;
		}
	}
}

bool CollisionManagement2D::collisionBoxCollider2D(const Collider2D* left, const Collider2D* right)
{
	Vector3 arrLocal[4] =
	{
		Vector3(-0.5f, 0.5f, 0.f),
		Vector3(0.5f, 0.5f, 0.f),
		Vector3(0.5f, -0.5f, 0.f),
		Vector3(-0.5f, -0.5f, 0.f),
	};

	Vector3 arrProj[4] = {};

	arrProj[0] = XMVector3TransformCoord(arrLocal[1],
		left->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], left->GetColliderWorldMat());
	arrProj[1] = XMVector3TransformCoord(arrLocal[3],
		left->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], left->GetColliderWorldMat());

	arrProj[2] = XMVector3TransformCoord(arrLocal[1],
		right->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], right->GetColliderWorldMat());
	arrProj[3] = XMVector3TransformCoord(arrLocal[3],
		right->GetColliderWorldMat()) - XMVector3TransformCoord(arrLocal[0], right->GetColliderWorldMat());

	Vector3 vCenter = XMVector3TransformCoord(Vector3(0.f, 0.f, 0.f), right->GetColliderWorldMat()) - XMVector3TransformCoord(Vector3(0.f, 0.f, 0.f), left->GetColliderWorldMat());

	for (int i = 0; i < 4; ++i)
	{
		Vector3 proj = arrProj[i];
		proj.Normalize();
		
		float projDist = 0.f;
		for (int j = 0; j < 4; ++j)
		{
			projDist += fabsf(arrProj[j].Dot(proj));
		}
		projDist /= 2.f;

		float center = fabsf(vCenter.Dot(proj));

		if (projDist < center)
		{
			return false;
		}			
	}

	return true;
}

bool CollisionManagement2D::collisionCircleCollider2D(const Collider2D* left, const Collider2D* right)
{
	const float DIST = (left->GetColliderWorldMat().Translation() -
		right->GetColliderWorldMat().Translation()).Length();

	return DIST < left->GetRadius() + right->GetRadius();
}

bool CollisionManagement2D::collisionBoxAndCircleCollider2D(const Collider2D* box, const Collider2D* circle)
{
	constexpr const Vector3 vertexPosArray[4] =
	{
		Vector3(-0.5f, 0.5f, 0.f),
		Vector3(0.5f, 0.5f, 0.f),
		Vector3(0.5f, -0.5f, 0.f),
		Vector3(-0.5f, -0.5f, 0.f),
	};
	const Matrix& BOX_WORLD_MATRIX = box->GetColliderWorldMat();
	Vector3 worldVertexPosArray[4] = {};

	for (int i = 0; i < 2; ++i)
	{
		worldVertexPosArray[i] = XMVector3TransformCoord(vertexPosArray[i], BOX_WORLD_MATRIX);
	}

	Vector3 right = (worldVertexPosArray[1] - worldVertexPosArray[0]);
	right.Normalize();

	float rotationRadinZ = acos(right.Dot(Vector3::Right));

	if (worldVertexPosArray[0].y > worldVertexPosArray[1].y)
	{
		rotationRadinZ = -rotationRadinZ;
	}

	const Matrix& BOX_ROTATION = Matrix::CreateRotationZ(-rotationRadinZ);

	Matrix boxZeroWorldMAtrix = BOX_WORLD_MATRIX;
	boxZeroWorldMAtrix._41 = 0.f; boxZeroWorldMAtrix._42 = 0.f; boxZeroWorldMAtrix._43 = 0.f;

	//rotating
	boxZeroWorldMAtrix = boxZeroWorldMAtrix * BOX_ROTATION;
	
	//Move to origin pos
	for (int i = 0; i < 4; ++i)
	{		
		worldVertexPosArray[i] = XMVector3TransformNormal(vertexPosArray[i], boxZeroWorldMAtrix);
	}

	//Move to origin pos
	Matrix MOVE_CIRCLE_MATRIX = {};
	MOVE_CIRCLE_MATRIX.Translation(-circle->GetColliderWorldMat().Translation());

	//Rotation radian
	const Matrix& CIRCLE_MATRIX = box->GetColliderWorldMat() * MOVE_CIRCLE_MATRIX;
	//Revolution
	const Vector3 CIRCLE_POS = (CIRCLE_MATRIX * BOX_ROTATION).Translation();

	//Circle pos Test
	Vector3 testPos = CIRCLE_POS;

	if (CIRCLE_POS.x < worldVertexPosArray[0].x)
	{
		testPos.x = worldVertexPosArray[0].x;
	}
	else if (CIRCLE_POS.x > worldVertexPosArray[1].x)
	{
		testPos.x = worldVertexPosArray[1].x;
	}

	if (CIRCLE_POS.y > worldVertexPosArray[0].y)
	{
		testPos.y = worldVertexPosArray[0].y;
	}
	else if (CIRCLE_POS.y < worldVertexPosArray[3].y)
	{
		testPos.y = worldVertexPosArray[3].y;
	}

	const float DIST_X = CIRCLE_POS.x - testPos.x;
	const float DIST_Y = CIRCLE_POS.y - testPos.y;
	const float RADIUS = circle->GetRadius();

	return (DIST_X * DIST_X) + (DIST_Y * DIST_Y) <= RADIUS * RADIUS;
}
