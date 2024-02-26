#include "pch.h"
#include "GetScriptComponent.h"
#include "ScriptComponent.h"

eScriptComponentType GetScriptComponent(ScriptComponent* component)
{
    return component->GetScriptType();
}
