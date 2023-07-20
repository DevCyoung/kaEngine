#include "pch.h"
#include "ParentTest.h"
#include "Components.h"

ParentTest::ParentTest()
    : ScriptComponent(eScriptComponentType::ParentTest)
	, mSclae(1.f)
{
}

ParentTest::~ParentTest()
{
}

void ParentTest::initialize()
{
}

void ParentTest::update()
{
	Transform* const transform = GetOwner()->GetComponent<Transform>();

	

	if (gInput->GetKey(eKeyCode::P))
	{		
		mSclae -= gDeltaTime;
	}

	if (gInput->GetKey(eKeyCode::O))
	{		
		mSclae += gDeltaTime;
	}

	transform->SetScale(mSclae, mSclae, 1.f);
}

void ParentTest::lateUpdate()
{
}

