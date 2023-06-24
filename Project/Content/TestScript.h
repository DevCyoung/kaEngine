#pragma once
#include <Engine/Script.h>
#include "EnumScript.h"

class TestScript : public engine::Script
{
public:
	TestScript();
	virtual ~TestScript();
	TestScript(const TestScript&) = delete;
	TestScript& operator=(const TestScript&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPT_TYPE(TestScript);