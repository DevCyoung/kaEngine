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
