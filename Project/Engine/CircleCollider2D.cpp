#include "pch.h"
#include "Transform.h"
#include "CircleCollider2D.h"
#include "RenderTargetRenderer.h"
#include "DebugRenderer2D.h"

CircleCollider2D::CircleCollider2D()
	: Collider2D(eComponentType::CircleCollider2D, eCollider2DType::Circle)
{
}

CircleCollider2D::~CircleCollider2D()
{
}

void CircleCollider2D::initialize()
{
}

void CircleCollider2D::update()
{
}

void CircleCollider2D::lateUpdate()
{
	mColliderWorldMat = XMMatrixScaling(mRadius * 2.f, mRadius * 2.f, mRadius * 2.f);
	mColliderWorldMat *= XMMatrixTranslation(mOffset.x, mOffset.y, mOffset.z);
	mColliderWorldMat *= GetOwner()->GetComponent<Transform>()->GetWorldMatrix();

	DebugRenderer2D* debugRenderer = GetOwner()->GetRenderTargetRenderer()->GetDebugRenderer();

	Vector4 color = Vector4(0.f, 1.f, 0.f, 1.f);

	if (mCollisionCount > 0)
	{
		color = Vector4(1.f, 0.f, 0.f, 1.f);
	}

	debugRenderer->DrawCircle2D2(mColliderWorldMat, 0.f, color);
}
