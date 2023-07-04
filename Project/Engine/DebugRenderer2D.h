#pragma once
#include "RenderComponent.h"

REGISTER_COMPONENT_TYPE(DebugRenderer2D);

class DebugRenderer2D : public RenderComponent
{
public:
	DebugRenderer2D();
	virtual ~DebugRenderer2D();
	DebugRenderer2D(const DebugRenderer2D&) = delete;
	DebugRenderer2D& operator=(const DebugRenderer2D&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
public:
	virtual void render(const Camera* const camera) override final;

};
