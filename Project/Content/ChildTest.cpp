#include "pch.h"
#include "ChildTest.h"
#include "Components.h"

ChildTest::ChildTest()
    : ScriptComponent(eScriptComponentType::ChildTest)
{
}

ChildTest::~ChildTest()
{
}

void ChildTest::initialize()
{
}

void ChildTest::update()
{
    Transform* transform = GetOwner()->GetComponent<Transform>();
    Vector3 right = transform->GetRight();
    float ditance = right.Length();
    (void)ditance;
}

void ChildTest::lateUpdate()
{
}
