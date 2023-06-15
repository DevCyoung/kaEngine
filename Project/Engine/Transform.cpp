#include "pch.h"
#include "Transform.h"

namespace engine
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
	{
	}

	Transform::~Transform()
	{
	}

	void Transform::initialize()
	{
	}

	void Transform::update()
	{
	}

	void Transform::lateUpdate()
	{
	}
		
	void Transform::render()
	{
	}
}