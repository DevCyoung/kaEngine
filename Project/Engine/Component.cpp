#include "pch.h"
#include "Component.h"

Component::Component(const eComponentType COMPONENT_TYPE)
	: mType(COMPONENT_TYPE)
	, mOwner(nullptr)
{
}

Component::~Component()
{
}

void Component::initialize()
{
}

void Component::update()
{
}

void Component::fixedUpdate()
{
}

void Component::lateUpdate()
{
}

void Component::lastUpdate()
{
}





