#include "pch.h"
#include "Transform.h"
#include "EngineMath.h"

Transform::Transform()
	: Component(eComponentType::Transform)
	, mPosition(Vector3::Zero)
	, mRotation(Vector3::Zero)
	, mScale(Vector3::One)
	, mForward(Vector3::Forward)
	, mRight(Vector3::Right)
	, mUp(Vector3::Up)
	, mWorld(Matrix::Identity)
{
}

Transform::~Transform()
{
}

Matrix Transform::CreateWorldMatrix(const Vector3& POSITION, const Vector3& ROTATION, const Vector3& SCALE)
{
	Matrix world = Matrix::Identity;

	Matrix scaleMatrix = Matrix::CreateScale(SCALE);

	Matrix rotationMatrix = {};
	rotationMatrix = Matrix::CreateRotationX(Deg2Rad(ROTATION.x));
	rotationMatrix *= Matrix::CreateRotationY(Deg2Rad(ROTATION.y));
	rotationMatrix *= Matrix::CreateRotationZ(Deg2Rad(ROTATION.z));

	Matrix positionMatrix = {};
	positionMatrix.Translation(POSITION);

	world *= scaleMatrix;
	world *= rotationMatrix;
	world *= positionMatrix;

	return world;
}

void Transform::initialize()
{
}

void Transform::update()
{
}

void Transform::lateUpdate()
{
	mWorld = Transform::CreateWorldMatrix(mPosition, mRotation, mScale);

	GameObject* const parent = GetOwner()->GetParentOrNull();

	if (GetOwner()->GetParentOrNull())
	{
		//부모공간으로 들어간다.
		//부모가 이미 계산이 되어있어야한다.
		mWorld *= parent->GetComponent<Transform>()->mWorld;
	}

	//FIXME
	mUp = XMVector3TransformNormal(Vector3::Up, mWorld);
	mForward = XMVector3TransformNormal(Vector3::Forward, mWorld);
	mRight = XMVector3TransformNormal(Vector3::Right, mWorld);
}

