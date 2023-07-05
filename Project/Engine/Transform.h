#pragma once
#include "Component.h"

REGISTER_COMPONENT_TYPE(Transform);

class Transform : public Component
{
public:
	Transform();
	virtual ~Transform();
	Transform(const Transform&) = delete;
	Transform& operator=(const Transform&) = delete;

	void SetPosition(const Vector3& POSITION) { mPosition = POSITION; }
	void SetRotation(const Vector3& ROTATION) { mRotation = ROTATION; }
	void SetScale(const Vector3& SCALE) { mScale = SCALE; }

	void SetPosition(const float X, const float Y, const float Z) { mPosition = Vector3(X, Y, Z); }
	void SetRotation(const float X, const float Y, const float Z) { mRotation = Vector3(X, Y, Z); }
	void SetScale(const float X, const float Y, const float Z) { mScale = Vector3(X, Y, Z); }

	const Vector3& GetPosition() const { return mPosition; }
	const Vector3& GetRotation() const { return mRotation; }
	const Vector3& GetScale() const { return mScale; }

	const Vector3& GetForward() const { return mForward; }
	const Vector3& GetRight() const { return mRight; }
	const Vector3& GetUp() const { return mUp; }

	const Matrix& GetWorldMatrix() const { return mWorld; }

	static Matrix CreateWorldMatrix(const Vector3& POSITION, const Vector3& ROTATION, const Vector3& SCALE);

private:
	virtual void initialize() override final;
	virtual void update() override final;
	virtual void lateUpdate() override final;	

private:
	Vector3 mPosition;
	Vector3 mRotation;
	Vector3 mScale;
	Vector3 mForward;
	Vector3 mRight;
	Vector3 mUp;
	Matrix mWorld;
};
