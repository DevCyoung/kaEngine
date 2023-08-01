#include "pch.h"
#include "ParticleSystem.h"

ParticleSystem::ParticleSystem()
	: RenderComponent(eComponentType::ParticleSystem)
{
}

ParticleSystem::~ParticleSystem()
{
}

void ParticleSystem::initialize()
{
}

void ParticleSystem::update()
{
	RenderComponent::update();
}

void ParticleSystem::lateUpdate()
{
}

void ParticleSystem::render(const Camera* const camera)
{
	(void)camera;
}
