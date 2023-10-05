#include "pch.h"
#include "CameraWall.h"
#include "Components.h"

CameraWall::CameraWall()
    : ScriptComponent(eScriptComponentType::CameraWall)
    , mCameraWallType(eCameraWallType::Left)
{
}

CameraWall::~CameraWall()
{
}

void CameraWall::initialize()
{
}

void CameraWall::update()
{
}

void CameraWall::lateUpdate()
{
}
