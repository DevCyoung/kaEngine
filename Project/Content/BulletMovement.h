#pragma once
#include <Engine/Script.h>
#include "EnumScript.h"

class BulletMovement : public engine::Script
{
public:
	BulletMovement();
	virtual ~BulletMovement();
	BulletMovement(const BulletMovement&) = delete;
	BulletMovement& operator=(const BulletMovement&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;
};

REGISTER_SCRIPT_TYPE(BulletMovement);
