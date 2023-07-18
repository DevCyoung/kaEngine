		#include "pch.h"
#include "RectCollider2D.h"
#include "Transform.h"
#include "RenderTargetRenderer.h"
#include "DebugRenderer2D.h"

RectCollider2D::RectCollider2D()
	: Collider2D(eComponentType::RectCollider2D, eCollider2DType::Box)
{
}

RectCollider2D::~RectCollider2D()
{
}

void RectCollider2D::initialize()
{
}

void RectCollider2D::update()
{		
}

void RectCollider2D::lateUpdate()
{
	const Transform* const P_TRANSFORM = GetOwner()->GetComponent<Transform>();

	mColliderWorldMat = XMMatrixScaling(mSize.x, mSize.y, mSize.z);
	mColliderWorldMat *= XMMatrixTranslation(mOffset.x, mOffset.y, mOffset.z);
	mColliderWorldMat *= P_TRANSFORM->GetWorldMatrix();

	DebugRenderer2D* debugRenderer = GetOwner()->GetRenderTargetRenderer()->GetDebugRenderer();

	Vector4 color = Vector4(0.f, 1.f, 0.f, 1.f);

	if (mCollisionCount > 0)
	{
		color = Vector4(1.f, 0.f, 0.f, 1.f);
	}

	debugRenderer->DrawRect2D3(mColliderWorldMat, 0.f, color);
}
