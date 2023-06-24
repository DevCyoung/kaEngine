#pragma once
#include <Engine/Script.h>

class CameraScript : public engine::Script
{
public:
	CameraScript();
	virtual ~CameraScript();
	CameraScript(const CameraScript&) = delete;
	CameraScript& operator=(const CameraScript&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

