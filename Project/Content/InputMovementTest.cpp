#include "pch.h"
#include "InputMovementTest.h"
#include "Components.h"

InputMovementTest::InputMovementTest()
    : ScriptComponent(eScriptComponentType::InputMovementTest)
{
}

InputMovementTest::~InputMovementTest()
{
}

void InputMovementTest::initialize()
{
}

void InputMovementTest::update()
{
	const float MOVE_SPEED = 200.f;
	Transform* const transform = GetOwner()->GetComponent<Transform>();

	Vector3 pos = transform->GetPosition();
	Vector3 dir = Vector3::Zero;

	if (gInput->GetKey(eKeyCode::LEFT))
	{
		dir.x -= 1.f;
	}
	else if (gInput->GetKey(eKeyCode::RIGHT))
	{
		dir.x += 1.f;
	}

	if (gInput->GetKey(eKeyCode::UP))
	{
		dir.y += 1.f;
	}
	else if (gInput->GetKey(eKeyCode::DOWN))
	{
		dir.y -= 1.f;
	}

	dir.Normalize();
	pos += dir * gDeltaTime * MOVE_SPEED;
	transform->SetPosition(pos);


}

#include <Engine/GameSystem.h>
#include <Engine/Physics2D.h>
#include <Engine/RenderTargetRenderer.h>
#include <Engine/DebugRenderer2D.h>
void InputMovementTest::lateUpdate()
{
	GameSystem* const gameSystem = GetOwner()->GetGameSystem();
	DebugRenderer2D* const debugRenderer2D = gameSystem->GetRenderTargetRenderer()->GetDebugRenderer();
	Physics2D* const physcis2D = gameSystem->GetPhysics2D();
	Transform* const transform = GetOwner()->GetComponent<Transform>();		

	const Vector3& POS = transform->GetPosition();
	RayCast2DHitInfo hitInfo = {};

	const Vector2& DIRECTION = Vector2(1.f, -1.f);
	const float DISTANCE = 500.f;

	if (physcis2D->RayCastHit2D(Vector2(POS.x, POS.y), DIRECTION, DISTANCE, eLayerType::Default, &hitInfo))
	{
		debugRenderer2D->DrawLine2D2(POS, DIRECTION, DISTANCE, 0.f, Vector4(1.f, 0.f, 1.f, 1.f));
	}
	else
	{
		debugRenderer2D->DrawLine2D2(POS, DIRECTION, DISTANCE, 0.f, Vector4(1.f, 1.f, 1.f, 1.f));
	}	
}
