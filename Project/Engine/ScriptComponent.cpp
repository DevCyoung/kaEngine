#include "pch.h"
#include "ScriptComponent.h"
#include "Transform.h"

ScriptComponent::ScriptComponent(const eScriptComponentType scriptComonentType)
	: Component(eComponentType::ScriptComponent)
	, mScriptType(scriptComonentType)	
{
}

ScriptComponent::~ScriptComponent()
{
}

void ScriptComponent::initialize()
{
}

void ScriptComponent::update()
{
}
void ScriptComponent::lateUpdate()
{
}

void ScriptComponent::onCollisionEnter(Collider2D* other)
{
	(void)other;
}

void ScriptComponent::onCollisionStay(Collider2D* other)
{
	(void)other;
}

void ScriptComponent::onCollisionExit(Collider2D* other)
{
	(void)other;
}
