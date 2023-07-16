#include "pch.h"
#include "LerpTest.h"
#include "Components.h"
#include <Engine/EngineMath.h>


LerpTest::LerpTest()
    : ScriptComponent(eScriptComponentType::LerpTest)
{
}

LerpTest::~LerpTest()
{
}

void LerpTest::initialize()
{
    mStartPos = GetOwner()->GetComponent<Transform>()->GetPosition();
}

void LerpTest::update()
{
    Transform* transform = GetOwner()->GetComponent<Transform>();    

    mStartPos.x += 300.f * cosf(gGlobalTime) * gDeltaTime;

    transform->SetPosition(mStartPos);

}

void LerpTest::lateUpdate()
{
}
