#pragma once
#include <Engine/Script.h>
#include "EnumScript.h"

class $safeitemname$ : public engine::Script
{
public:
	$safeitemname$();
	virtual ~$safeitemname$();
	$safeitemname$(const $safeitemname$&) = delete;
	$safeitemname$& operator=(const $safeitemname$&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPT_TYPE($safeitemname$);
