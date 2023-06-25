#pragma once
#include <Engine/Script.h>
#include "EnumScript.h"

class Findingin : public engine::Script
{
public:
	Findingin();
	virtual ~Findingin();
	Findingin(const Findingin&) = delete;
	Findingin& operator=(const Findingin&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPT_TYPE(Findingin);
