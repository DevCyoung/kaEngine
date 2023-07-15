#pragma once
#include "Component.h"

REGISTER_COMPONENT_TYPE(Collider2D);

class Collider2D : public Component
{
public:
	Collider2D();
	virtual ~Collider2D();
	Collider2D(const Collider2D&) = delete;
	Collider2D& operator=(const Collider2D&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;

};
