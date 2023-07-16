#include "pch.h"
#include "Collider2D.h"
#include "Transform.h"
#include "RenderTargetRenderer.h"
#include "DebugRenderer2D.h"
#include "ScriptComponent.h"

Collider2D::Collider2D(const eComponentType componentType,
	const eCollider2DType colllider2DType)
	: Component(componentType)
	, mColllider2DType(colllider2DType)
	, mColliderWorldMat{}
	, mScale{ 100.f, 100.f, 1.f }
	, mOffset{}
	, mCollisionCount(0)
	, mRadius(1000.f)
{

}

Collider2D::~Collider2D()
{
}

void Collider2D::initialize()
{
}

void Collider2D::update()
{
}

void Collider2D::lateUpdate()
{

}

void Collider2D::OnCollisionEnter(Collider2D* other)
{
	++mCollisionCount;

	const std::vector<ScriptComponent*>& scripts = GetOwner()->GetScriptComponents();

	for (ScriptComponent* script : scripts)
	{
		script->OnCollisionEnter(other);
	}
}

void Collider2D::OnCollisionStay(Collider2D* other)
{
	const std::vector<ScriptComponent*>& scripts = GetOwner()->GetScriptComponents();

	for (ScriptComponent* script : scripts)
	{
		script->OnCollisionStay(other);
	}
}

void Collider2D::OnCollisionExit(Collider2D* other)
{
	--mCollisionCount;

	const std::vector<ScriptComponent*>& scripts = GetOwner()->GetScriptComponents();

	for (ScriptComponent* script : scripts)
	{
		script->OnCollisionExit(other);
	}
}
