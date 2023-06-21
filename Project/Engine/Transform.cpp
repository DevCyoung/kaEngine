#include "pch.h"
#include "Transform.h"

namespace engine
{
	Transform::Transform()
		: Component(eComponentType::Transform)
		, mPosition(Vector3::Zero)
		, mRotation(Vector3::Zero)
		, mScale(Vector3::One)
		, mForward(Vector3::Forward)
		, mRight(Vector3::Right)
		, mUp(Vector3::Up)
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
		mWorld = Matrix::Identity;

		Matrix scale = Matrix::CreateScale(mScale);		

		Matrix rotation = {};
		rotation = Matrix::CreateRotationX(mRotation.x);
		rotation *= Matrix::CreateRotationY(mRotation.y);
		rotation *= Matrix::CreateRotationZ(mRotation.z);

		Matrix position = {};
		position.Translation(mPosition);

		mWorld *= scale;
		mWorld *= rotation;
		mWorld *= position;

		//FIXME

		//mUp = XMVector3TransformNormal(Vector3::Up, mWorld);
		//mForward = XMVector3TransformNormal(Vector3::Forward, mWorld);
		//mRight = XMVector3TransformNormal(Vector3::Right, mWorld);
	}
		
	void Transform::render()
	{
	}
}