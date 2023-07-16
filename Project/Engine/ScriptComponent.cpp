#include "pch.h"
#include "ScriptComponent.h"

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

void ScriptComponent::OnCollisionEnter(Collider2D* other)
{
	(void)other;
}

void ScriptComponent::OnCollisionStay(Collider2D* other)
{
	(void)other;
}

void ScriptComponent::OnCollisionExit(Collider2D* other)
{
	(void)other;
}
