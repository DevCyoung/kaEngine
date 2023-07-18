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

void InputMovementTest::lateUpdate()
{
}
