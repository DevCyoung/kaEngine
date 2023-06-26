#include "pch.h"
#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(eScriptComponentType type)
	: Component(eComponentType::ScriptComponent)
	, mScriptType(type)
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
void ScriptComponent::render()
{
}
