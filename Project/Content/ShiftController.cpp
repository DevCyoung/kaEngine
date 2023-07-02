#include "pch.h"
#include "ShiftController.h"
#include "Components.h"
#include "ResourceManager.h"
#include <Engine/InputManager.h>

ShiftController::ShiftController()
    : ScriptComponent(eScriptComponentType::ShiftController)
{
}

ShiftController::~ShiftController()
{
}

void ShiftController::initialize()
{
}

void ShiftController::update()
{    
    if (gInput->GetKey(eKeyCode::LSHIFT))
    {
        GetComponent<MeshRenderer>()->SetMaterial(gResourceManager->FindOrNullByRelativePath<Material>(L"UIShift01"));
    }
    else
    {
        GetComponent<MeshRenderer>()->SetMaterial(gResourceManager->FindOrNullByRelativePath<Material>(L"UIShift00"));
    }
    
}

void ShiftController::lateUpdate()
{
}

void ShiftController::render()
{
}