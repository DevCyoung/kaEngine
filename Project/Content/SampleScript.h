#pragma once
#include <Engine/Script.h>
#include "EnumScript.h"

class SampleScript : public engine::Script
{
public:
	SampleScript();
	virtual ~SampleScript();
	SampleScript(const SampleScript&) = delete;
	SampleScript& operator=(const SampleScript&) = delete;

private:
	virtual void initialize() override;
	virtual void update() override;
	virtual void lateUpdate() override;
	virtual void render() override;
};

REGISTER_SCRIPT_TYPE(SampleScript);