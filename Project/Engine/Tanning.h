#pragma once
#include "Component.h"

REGISTER_COMPONENT_TYPE(Tanning);

class Tanning : public Component
{
public:
	Tanning();
	virtual ~Tanning();
	Tanning(const Tanning&) = delete;
	Tanning& operator=(const Tanning&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render() override final;

};
