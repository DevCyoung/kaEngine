#pragma once
#include <Engine/Script.h>
#include "EnumScript.h"

class diffTest : public engine::Script
{
public:
	diffTest();
	virtual ~diffTest();
	diffTest(const diffTest&) = delete;
	diffTest& operator=(const diffTest&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPT_TYPE(diffTest);
