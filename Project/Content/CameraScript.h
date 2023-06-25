#pragma once
#include <Engine/Script.h>
#include "EnumScript.h"

class CameraScript : public engine::Script
{
public:
	CameraScript();
	virtual ~CameraScript();
	CameraScript(const CameraScript&) = delete;
	CameraScript& operator=(const CameraScript&) = delete;

private:
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
};

REGISTER_SCRIPT_TYPE(CameraScript);
