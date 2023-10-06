#pragma once
#include <Engine/ScriptComponent.h>
#include "EnumScriptComponent.h"

REGISTER_SCRIPTCOMPONENT_TYPE(GlassParticle);

class GlassParticle : public ScriptComponent
{
public:
	GlassParticle();
	virtual ~GlassParticle();
	GlassParticle(const GlassParticle&) = delete;
	GlassParticle& operator=(const GlassParticle&) = delete;

public:
	void Shot(const std::wstring& animName, Vector2 velocity);

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void onCollisionEnter(Collider2D* other) override final;

	bool mbRotation;
};
