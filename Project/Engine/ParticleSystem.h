#pragma once
#include "RenderComponent.h"

REGISTER_COMPONENT_TYPE(ParticleSystem);

class Mesh;
class Material;
class Texture;


class ParticleSystem : public RenderComponent
{
public:
	ParticleSystem();
	virtual ~ParticleSystem();
	ParticleSystem(const ParticleSystem&) = delete;
	ParticleSystem& operator=(const ParticleSystem&) = delete;

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;
	virtual void render(const Camera* const camera) override final;
};

