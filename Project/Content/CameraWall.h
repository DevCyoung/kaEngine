#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(CameraWall);

enum class eCameraWallType
{	
	Left,
	Right,
	Up,
	Down	
};

class CameraWall : public ScriptComponent
{
public:
	CameraWall();
	virtual ~CameraWall();
	CameraWall(const CameraWall&) = delete;
	CameraWall& operator=(const CameraWall&) = delete;

	void SetCameraWallType(eCameraWallType type) { mCameraWallType = type; }
	eCameraWallType GetCameraWallType() const { return mCameraWallType; }

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

	eCameraWallType mCameraWallType;
};
