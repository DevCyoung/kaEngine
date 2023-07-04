#include "pch.h"
#include "ScriptComponent.h"

ScriptComponent::ScriptComponent(eScriptComponentType SCRIPT_COMPONENT_TYPE)
	: Component(eComponentType::ScriptComponent)
	, mScriptType(SCRIPT_COMPONENT_TYPE)
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
